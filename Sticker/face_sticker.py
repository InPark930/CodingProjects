import cv2 
# Open the device at the ID 0

cap = cv2.VideoCapture(0)

#To set the resolution


while(True):

# Capture frame-by-frame

    ret, frame = cap.read()
    frame = cv2.flip(frame,3)

# Display the resulting frame

    cv2.imshow('preview',frame)

#Waits for a user input to quit the application

    if cv2.waitKey(1) & 0xFF == ord('q'):

        break

# When everything done, release the capture

cap.release()

cv2.destroyAllWindows()
