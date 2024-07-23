import time
import serial
import serial.tools.list_ports
import threading

def read_from_port(serial_instance):
    buffer = ""
    while True:
        if serial_instance.in_waiting > 0:
            data = serial_instance.read(serial_instance.in_waiting).decode('utf-8')
            buffer += data
            # Pisahkan buffer berdasarkan baris baru
            lines = buffer.splitlines()
            for line in lines[:-1]:  # Semua baris kecuali yang terakhir
                print(f"Arduino: {line.strip()}")
            buffer = lines[-1]  # Simpan baris terakhir yang mungkin belum lengkap

def main():
    # Daftar port yang tersedia
    ports = serial.tools.list_ports.comports()
    serial_inst = serial.Serial()
    ports_list = []

    for one in ports:
        ports_list.append(str(one))
        print(str(one))

    # Pilih port COM
    com = input("Pilih nomor COM Port untuk Arduino #: ")

    use = None
    for i in range(len(ports_list)):
        if ports_list[i].startswith("COM" + str(com)):
            use = "COM" + str(com)
            print(f"Menggunakan port: {use}")
            break

    if use is None:
        print(f"COM{com} tidak tersedia.")
        return

    # Konfigurasi koneksi serial
    serial_inst.baudrate = 57600
    serial_inst.port = use
    serial_inst.timeout = 1  # Setel timeout untuk menghindari blokir

    try:
        serial_inst.open()
        print(f"Tersambung ke {use}")
    except serial.SerialException as e:
        print(f"Gagal membuka port serial {use}: {e}")
        return

    # Membuat thread untuk membaca dari port serial
    read_thread = threading.Thread(target=read_from_port, args=(serial_inst,))
    read_thread.daemon = True
    read_thread.start()

    while True:
        command = input("Perintah ke Arduino: ")
        if command.lower() == 'exit':
            serial_inst.close()
            print("Koneksi ditutup.")
            break

        # serial_inst.write((command + "\n").encode('utf-8'))

        # Tunggu sejenak setelah mengirim perintah
        time.sleep(0.1)

if __name__ == "__main__":
    main()
