/*
 * task_midi.c
 *
 */

#include "task_midi.h"
#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_midi.h"
#include "usbd_midi_if.h"


osThreadId MIDITaskHandle;
QueueHandle_t midi_event_queue;
uint8_t midi_msg_buffer[4];
extern USBD_HandleTypeDef hUsbDevice;

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
            // Construct USB MIDI packet with correct Code Index Number (CIN)
            // Cable Number = 0, CIN = message_type upper 4 bits
            usb_midi_report[0] = (midi_ev.message_type >> 4) & 0x0F;
            usb_midi_report[1] = midi_ev.message_type | (midi_ev.channel & 0x0F);
            usb_midi_report[2] = midi_ev.note;
            usb_midi_report[3] = midi_ev.value;
            while (MIDI_GetState() != MIDI_IDLE) {
                continue;
            };
            MIDI_SendReport(usb_midi_report, 4);
        }
	}
}

void USBD_MIDI_DataInHandler(uint8_t *usb_rx_buffer, uint8_t usb_rx_buffer_length)
{
  while (usb_rx_buffer_length && *usb_rx_buffer != 0x00)
  {
//    cable = usb_rx_buffer[0] >> 4;
//    code = usb_rx_buffer[0] & 0x0F;
//    message = usb_rx_buffer[1] >> 4;
//    channel = usb_rx_buffer[1] & 0x0F;
//    messageByte1 = usb_rx_buffer[2];
//    messageByte2 = usb_rx_buffer[3];
    usb_rx_buffer += 4;
    usb_rx_buffer_length -= 4;
  }
}
