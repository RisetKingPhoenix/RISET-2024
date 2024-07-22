import time
import serial.tools.list_ports

# Daftar port yang tersedia
ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()
portsList = []

for one in ports:
    portsList.append(str(one))
    print(str(one))

# Pilih port COM
com = input("Pilih nomor COM Port untuk Arduino #: ")

use = None
for i in range(len(portsList)):
    if portsList[i].startswith("COM" + str(com)):
        use = "COM" + str(com)
        print(use)
        break

if use is None:
    print(f"COM{com} tidak tersedia.")
else:
    # Konfigurasi koneksi serial
    serialInst.baudrate = 57600
    serialInst.port = use
    serialInst.timeout = 1  # Setel timeout untuk menghindari blokir

    try:
        serialInst.open()
        print(f"Tersambung ke {use}")
    except serial.SerialException as e:
        print(f"Gagal membuka port serial {use}: {e}")
        exit()

    while True:
        command = input("Perintah ke Arduino: ")
        serialInst.write(command.encode('utf-8'))

        if command.lower() == 'exit':
            serialInst.close()
            print("Koneksi ditutup.")
            break

        # Tunggu sejenak setelah mengirim perintah
        time.sleep(0.1)

        # Membaca dari port serial
        while True:
            if serialInst.in_waiting > 0:
                response = serialInst.read(serialInst.in_waiting).decode('utf-8').strip()
                print(f": {response}")
            else:
                break
