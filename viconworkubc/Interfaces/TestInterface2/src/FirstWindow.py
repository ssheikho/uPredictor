
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import csv
import sys
import time

from create_numbers2_class import *
from windowtitle_class import *
from create_pictures_class import *

class Firstwindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initialDialog()

        self.setWindowTitle("Caris Lab - University of British Columbia")
        self.create_layout()
        self.i = 0
        self.numRounds = 0
        self.palette = QPalette()
        self.palette.setColor(QPalette.Background, Qt.white)

        #For saving current colour, number, and position


    def create_layout(self):
        #Add widgets

        self.numbers = Create_numbers()

        self.button_new = QPushButton("New")

        HLine = QFrame()
        HLine.setFrameStyle(QFrame.HLine)



        # create layout to hold widgets
        self.initial_layout = QVBoxLayout()

        self.initial_layout.addWidget(self.numbers)

        self.initial_layout.addWidget(self.button_new)


        self.select_widget = QWidget()
        self.select_widget.setLayout(self.initial_layout)

        self.setCentralWidget(self.select_widget)

        self.button_new.clicked.connect(self.button_press)

    def button_press(self):

        self.date = time.strftime("%d_%m_%Y")

        #Retrieve array of strings '1R', '3B', etc. for the number and associated colour of each ball
        numCol = self.numbers.methods(self.i)
        #Retreive array of randomized position of balls
        positions = self.numbers.methods2()
        numColours = [numCol[positions[0]], numCol[positions[1]], numCol[positions[2]], numCol[positions[3]]]

        #output to CSV file current setup
        resultFile = open(self.Name + "_" + self.date + ".csv", "a")
        writer = csv.writer(resultFile, dialect='excel', lineterminator='\n')
        if self.i == 0 and self.numRounds == 0:
            writer.writerows([["Subject Name", str(self.Name), "Subject Age", str(self.Age), "Subject Gender", str(self.Gender)],[]])
        writer.writerows([[],["Trial " + str(self.i + self.numRounds*24) ], [numCol[0], numCol[1], numCol[2], numCol[3]], [], [numColours[0], numColours[1]], [numColours[2], numColours[3]], []])

        self.i = self.i + 1
        print(self.i)
        if self.i == 24:
            self.i = 0
            self.numRounds += 1
            self.numbers.methods(self.i)
            self.numbers.methods2()

    def initialDialog(self):

        msg = QDialog()
        msg.setWindowTitle("Subject Information")

        grid = QGridLayout()
        msg.setLayout(grid)

        msg.setMinimumHeight(100)
        msg.setMinimumWidth(200)

        nameLabel = QLabel("Name:", msg)
        grid.addWidget(nameLabel, 1, 0)
        self.nameField = QLineEdit(msg)
        grid.addWidget(self.nameField, 1,1)

        ageLabel = QLabel("Age:", msg)
        grid.addWidget(ageLabel, 2, 0)
        self.ageField = QLineEdit(msg)
        grid.addWidget(self.ageField, 2,1)

        self.malebutton = QRadioButton("Male")
        self.femalebutton = QRadioButton("Female")
        self.otherbutton = QRadioButton("Other")
        genderLabel = QLabel("Gender")

        grid.addWidget(genderLabel, 3, 0)
        grid.addWidget(self.malebutton, 3, 1)
        grid.addWidget(self.femalebutton, 4, 1)
        grid.addWidget(self.otherbutton, 5, 1)

        StartButton = QPushButton("Start")
        grid.addWidget(StartButton)
        StartButton.clicked.connect(self.buttonDialog)

        msg.exec_()

    def buttonDialog(self):

        if self.malebutton.isChecked():
            self.gender = 'Male'
        elif self.femalebutton.isChecked():
            self.gender = 'Female'
        else:
            self.gender = 'Other'

        self.Name = self.nameField.text()
        self.Age = self.ageField.text()
        self.Gender = self.gender

        QCoreApplication.instance().quit()

def main():
    simulation = QApplication(sys.argv)
    window = Firstwindow()

    palette = QPalette()
    palette.setColor(QPalette.Background, Qt.white)
    window.setPalette(palette)
    window.show()
    window.raise_()
    simulation.exec_()

if __name__ == "__main__":
    main()