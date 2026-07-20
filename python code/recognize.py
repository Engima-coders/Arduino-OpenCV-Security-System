import cv2
import serial
import time

arduino = serial.Serial('COM5', 9600)
time.sleep(3)

door_unlocked = False
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')

faceCascade = cv2.CascadeClassifier(
    cv2.data.haarcascades +
    'haarcascade_frontalface_default.xml'
)
authorized_sent = False
unknown_sent = False
font = cv2.FONT_HERSHEY_SIMPLEX

# Names corresponding to IDs
names = ['', 'User']

cam = cv2.VideoCapture(0)
if not cam.isOpened():
    print("Cannot open camera")
    exit()

cam.set(3, 640)
cam.set(4, 480)

while True:

    ret, img = cam.read()
    if not ret:
     print("Failed to capture frame")
     break
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,
        minSize=(100, 100)
    )

    for (x, y, w, h) in faces:

        cv2.rectangle(
            img,
            (x, y),
            (x+w, y+h),
            (0, 255, 0),
            2
        )

        id, confidence = recognizer.predict(
            gray[y:y+h, x:x+w]
        )

        if confidence < 60:
          name = names[id]
          confidence_text = f"{100 - confidence:.0f}%"
          if not authorized_sent:
            arduino.write(b'F')
            print("Face Verified")
            authorized_sent = True
            unknown_sent=False

        else:
          if not unknown_sent:  
           name = "Unknown"
           confidence_text = f"{100 - confidence:.0f}%"
           
           unknown_sent=True
           authorized_sent=False
            

        cv2.putText(
            img,
            str(name),
            (x+5, y-5),
            font,
            1,
            (255,255,255),
            2
        )

        cv2.putText(
            img,
            confidence_text,
            (x+5, y+h-5),
            font,
            1,
            (255,255,0),
            1
        )
    if len(faces) == 0:
       authorized_sent = False
       unknown_sent=False
    cv2.imshow('Face Recognition', img)

    k = cv2.waitKey(10) & 0xff

    if k == 27:   # ESC key
        break

cam.release()
cv2.destroyAllWindows()