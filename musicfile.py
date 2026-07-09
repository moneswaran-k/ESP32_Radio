import socket
import wave
import time

ESP32_IP = "192.168.1.27"
PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

wav = wave.open("music_8bit.wav", "rb")

# Skip WAV header automatically
chunk_size = 256

print("Streaming...")

while True:

    data = wav.readframes(chunk_size)

    if not data:
        break

    sock.sendto(data, (ESP32_IP, PORT))

    # 22050 Hz, 8-bit mono
    time.sleep(chunk_size / 22050)

print("Finished!")