import numpy as np 
import pandas as pd 
import pickle 
import joblib 
from tensorflow.keras.models import load_model 
import sys 
# LIBRARY FOR GUI GENARATION 
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, 
QVBoxLayout, QLabel 
 
class MyApp(QWidget): 
    def __init__(self): 
        super().__init__() 
 
        # Initialize the UI 
        self.init_ui() 
 
    def init_ui(self): 
        # Set the layout 
        layout = QVBoxLayout() 
 
        # Create a label to display the text 
        self.label = QLabel("Click a button", self) 
        layout.addWidget(self.label) 
 
        # Create two buttons 
        button1 = QPushButton("Schizophrenia", self) 
        button2 = QPushButton("Epilepsy", self) 
 
        # Connect the buttons to their functions 
        button1.clicked.connect(self.Schizophrenia) 
        button2.clicked.connect(self.Epilepsy) 
 
        # Add buttons to the layout 
        layout.addWidget(button1) 
        layout.addWidget(button2) 
 
        # Set the layout for the window 
        self.setLayout(layout) 
 
        # Set window properties 
        self.setWindowTitle('Simple PyQt5 GUI') 
        self.setGeometry(100, 100, 300, 200) 
 
    def Epilepsy(self): 
        # Load your saved model 
        model = load_model("Epilepsy.h5") 
        i = 2 
        # Load the data 
        data = pd.read_csv('Epilepsy_input_data.csv') 
 
        # Convert the DataFrame to a NumPy array 
        data_array = data.values  # Extract numerical values 
 
        # Function to preprocess a single input and predict 
        def predict_single_input(model, input_sample): 
            # Ensure the input sample has the correct shape 
            input_sample = input_sample.reshape(1, 178, 1)  # Reshape 
for single input 
            prediction = model.predict(input_sample) 
            return prediction 
 single_input = data_array[i]  # Extract one sample (a single 
row) 
        prediction = predict_single_input(model, single_input) 
        if prediction[0][0] > 0.2: 
            self.label.setText("Epilepsy detected") 
            print(data_array) 
        else: 
            self.label.setText("Person is Healthy ") 
            print(data_array) 
 
    def Schizophrenia(self): 
        # Load the CSV file 
        x_test_loaded = pd.read_csv('Schizophrenia_input.csv') 
        i = 2 
        # input_data = np.array(input_data).reshape(1, -1) 
        input_data = x_test_loaded.iloc[i, :].values.reshape(1, -1) 
 
        # Load the model from the .pkl file 
        # with open('rf_clf.pkl', 'rb') as file: 
        model = joblib.load('Schizophrenia.pkl') 
 
        # Now you can use the loaded model for predictions 
        output = model.predict(input_data)  # Replace `input_data` 
with your actual input 
 
        if output == 1: 
            self.label.setText("Schizophrenia Detected") 
            print(input_data) 
        else: 
            self.label.setText("Person is Healthy") 
            print(input_data) 
 
# Create an application instance 
app = QApplication(sys.argv) 
 
# Create and show the GUI 
window = MyApp() 
window.show() 
 
# Run the application's event loop 
sys.exit(app.exec_())