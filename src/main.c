#include "main.h"
// Initialize Bluetooth drivers
void initializeBluetooth()
{
    int dev_id, sock;

    // Get the first available Bluetooth adapter
    dev_id = hci_get_route(NULL);
    if (dev_id < 0)
    {
        perror("No Bluetooth adapter found");
        exit(1);
    }

    // Open a Bluetooth socket using the found adapter
    sock = hci_open_dev(dev_id);
    if (sock < 0)
    {
        perror("HCI device open failed");
        exit(1);
    }

    // Initialize the Bluetooth device
    if (hci_le_set_scan_parameters(sock, 0x01, htobs(0x0010), htobs(0x0010), 0x00, 0x00, 1000) < 0)
    {
        perror("Set scan parameters failed");
        close(sock);
        exit(1);
    }

    // Close the Bluetooth socket
    close(sock);
}

uint16_t initiateConnection(const char *address)
{
    int dev_id, sock, status;
    bdaddr_t bdaddr; // Bluetooth address of the remote device
    uint16_t handle; // Connection handle

    // Initialize Bluetooth socket
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev(dev_id);

    // Set the Bluetooth address of the remote device
    str2ba(address, &bdaddr);

    // Create connection and get handle
    status = hci_create_connection(sock, &bdaddr, htobs(0x0008), 0, 0, &handle, 0);
    if (status < 0)
    {
        perror("Failed to connect");
        close(sock);
        exit(1);
    }

    // Close Bluetooth socket
    close(sock);

    return handle;
}

void handleDisconnect(uint16_t handle)
{
    int dev_id, sock, status;

    // Initialize Bluetooth socket
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev(dev_id);


    // Get handle
    status = hci_disconnect(sock, handle, HCI_OE_USER_ENDED_CONNECTION, 10000);
    if (status < 0)
    {
        perror("Failed to disconnect");
    }

    // Close Bluetooth socket
    close(sock);
}

void startAdvertising() {
    int dev_id, sock;
    uint8_t advertising_data[] = {0x02, 0x01, 0x06}; // Flags: LE General Discoverable, BR/EDR not supported
    uint8_t length = sizeof(advertising_data);

    // Initialize Bluetooth socket
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev(dev_id);

    // Stop advertising if already advertising
    hci_le_set_advertise_enable(sock, 0, 1000);

    // Set advertising data using raw HCI command
    uint8_t hci_advertising_data[32] = {0};
    hci_advertising_data[0] = length;
    memcpy(hci_advertising_data + 1, advertising_data, length);
    hci_send_cmd(sock, 0x08, 0x0008, length + 1, hci_advertising_data);

    // Enable advertising using raw HCI command
    uint8_t enable_advertising[] = { 0x01 };
    hci_send_cmd(sock, 0x08, 0x000A, 1, enable_advertising);

    // Close Bluetooth socket
    close(sock);
}


int main()
{
    startAdvertising();
    return 0;
}