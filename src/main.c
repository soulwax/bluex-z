#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

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

    // Initialize the Bluetooth device (you can add more initialization code here)
    if (hci_le_set_scan_parameters(sock, 0x01, htobs(0x0010), htobs(0x0010), 0x00, 0x00, 1000) < 0)
    {
        perror("Set scan parameters failed");
        close(sock);
        exit(1);
    }

    // Close the Bluetooth socket
    close(sock);
}

int main()
{
    initializeBluetooth();
    return 0;
}