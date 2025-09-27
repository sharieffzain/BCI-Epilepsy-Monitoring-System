import firebase_admin 
from firebase_admin import credentials, db 
import smtplib 
from time import sleep 
# Initialize Firebase Admin 
cred = credentials.Certificate('eeeg.json')  # Update the path 
firebase_admin.initialize_app(cred, { 
'databaseURL': 'https://smartparkingg-f7952-default-rtdb.firebaseio.com/'  
# Update the database URL 
}) 
# Email details 
sender_email = "alertcollege00@gmail.com" 
receiver_email = "zayan8399@gmail.com"  # Update the receiver email 
password = "xkiz ingm zdmu oywd"  # Update with the sender email password 
# Function to send email 
def send_email(): 
with smtplib.SMTP('smtp.gmail.com', 587) as server: 
server.starttls() 
server.login(sender_email, password) 
message = "Subject: Alert\n\n Take necessary action the patient has 
meet some issue please take action please" 
server.sendmail(sender_email, receiver_email, message) 
body = "patient has faced some critical stress level please take 
necessary action" 
print("Email sent successfully!") 
# Monitor flag in an infinite loop 
def monitor_flag(): 
ref = db.reference('flag')  # Replace 'flag' with the correct database 
node path 
while True: 
try: 
flag_value = ref.get() 
print(f"Current flag value: {flag_value}") 
if flag_value == 1: 
send_email() 
ref.set(0)  # Reset the flag to 0 after sending the email 
sleep(1)  # Check the flag every 10 seconds 
except Exception as e: 
print(f"An error occurred: {e}") 
if __name__ == "__main__": 
monitor_flag() 