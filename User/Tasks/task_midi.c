/*
 * task_midi.c
 *
 */

#include "task_midi.h"
#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_midi.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

osThreadId MIDITaskHandle;
QueueHandle_t midi_event_queue;
uint8_t midi_msg_buffer[4];

uint8_t usb_midi_report[4] = {
    0x19, // cable number, code index number
    0x90, // note on, channel 1
    0x3C, // note number
    0x7F, // velocity
};


static void TaskMIDI_task(void const *arg);

void TaskMIDI_createTask() {
    midi_event_queue = xQueueCreate(50, sizeof(midi_event_t));

	osThreadDef(MIDITask, TaskMIDI_task, osPriorityNormal, 0, 512);
	MIDITaskHandle = osThreadCreate(osThread(MIDITask), NULL);
}

int TaskMIDI_sendEvent(midi_event_t * ev) {
    if(xQueueSend(midi_event_queue, ev, 0) != pdPASS) {
        return -1;
    }
    return 0;
}

void TaskMIDI_task(void const *arg) {
	MX_USB_DEVICE_Init();
    midi_event_t midi_ev;
	while (1) {
        if(xQueueReceive(midi_event_queue, &midi_ev, portMAX_DELAY) == pdTRUE) {
            usb_midi_report[0] = 0x10 | ((midi_ev.message_type >> 4) & 0x0F);
            usb_midi_report[1] = midi_ev.message_type | (midi_ev.channel & 0x0F);
            usb_midi_report[2] = midi_ev.note;
            usb_midi_report[3] = midi_ev.value;
            while (USBD_MIDI_GetState(&hUsbDeviceFS) != MIDI_IDLE) {
                continue;
            };
            USBD_MIDI_SendReport(&hUsbDeviceFS, usb_midi_report, 4);
        }
	}
}
