import cv2
import time
import requests

ESP8266_IP = "http://192.168.1.100"  

def send_trigger_to_esp():
    try:
        requests.get(f"{ESP8266_IP}/trigger")
    except Exception as e:
        print("Failed to contact ESP8266:", e)

cap = cv2.VideoCapture(0)
time.sleep(2)
_, frame1 = cap.read()
_, frame2 = cap.read()

while True:
    diff = cv2.absdiff(frame1, frame2)
    gray = cv2.cvtColor(diff, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5,5), 0)
    _, thresh = cv2.threshold(blur, 20, 255, cv2.THRESH_BINARY)
    dilated = cv2.dilate(thresh, None, iterations=3)
    contours, _ = cv2.findContours(dilated, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours) > 0:
        print("Motion Detected!")
        ret, frame = cap.read()
        if ret:
            cv2.imwrite("captured.jpg", frame)
            send_trigger_to_esp()
        time.sleep(5)  

    frame1 = frame2
    ret, frame2 = cap.read()

    if not ret:
        break

cap.release()
cv2.destroyAllWindows()
