
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import csv
import sys
import time
import resources2
from create_balls2_class import *


class Mainwindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initialDialog()

        self.setWindowTitle("Caris Lab - University of British Columbia")
        self.create_layout()
        self.valid = True
        self.i = 0
        self.numRounds = 0
        self.palette = QPalette()
        self.palette.setColor(QPalette.Background, Qt.white)

        #For saving current colour, number, and position


    def create_layout(self):
        #Add widgets

        self.balls = Create_balls()

        self.tabs = QTabWidget()
        self.tab1 = QWidget()
        self.tab2 = QWidget()

        self.button_new_letters = QPushButton("New")
        self.button_new_numbers = QPushButton("New")


        self.first_tab = QVBoxLayout()
        self.first_tab.addWidget(self.balls.first_layout())
        self.first_tab.addWidget(self.button_new_letters)

        self.second_tab = QVBoxLayout()

        self.second_tab.addWidget(self.balls.second_layout1())
        self.second_tab.addSpacing(30)
        self.second_tab.addWidget(self.balls.second_layout2())
        self.second_tab.addSpacing(30)
        self.second_tab.addWidget(self.button_new_numbers)


        self.tab1.setLayout(self.first_tab)
        self.tab2.setLayout(self.second_tab)

        self.tabs.addTab(self.tab1, "Tab 1")
        self.tabs.addTab(self.tab2, "Tab 2")

        self.setCentralWidget(self.tabs)

        self.button_new_letters.clicked.connect(self.letters_button)
        self.button_new_numbers.clicked.connect(self.numbers_button)


    def letters_button(self):

        #Retrieve array of strings '1R', '3B', etc. for the number and associated colour of each ball
        self.numCol = self.balls.letters_method(self.i)
        self.p = self.balls.numbers_method(self.i)
        #Retreive array of randomized position of balls

        self.i = self.i + 1
        print(self.i)
        if self.i == 24:
            self.i = 0
            self.numRounds += 1
            self.numCol = self.balls.letters_method(self.i)
            self.p = self.balls.numbers_method(self.i)

        numBasket = self.p[0]
        rack_order = self.p[1]

        self.date = time.strftime("%d_%m_%Y")
        self.time = time.strftime("%H:%M:%S")

        # output to CSV file current setup
        resultFile = open(self.Name + "_" + self.date + ".csv", "a")
        writer = csv.writer(resultFile, dialect='excel', lineterminator='\n')
        if self.valid == True and self.numRounds == 0:
            writer.writerows(
                [["Subject Name", str(self.Name), "Subject Age", str(self.Age), "Subject Gender", str(self.Gender)],
                 []])
            self.valid = False
        writer.writerows([[], ["Trial " + str(self.i + self.numRounds * 24) + "  " + str(self.time)],
                          [self.numCol[0], self.numCol[1], self.numCol[2], self.numCol[3]], ["1", "2", "3", "4"], [], [rack_order[0], rack_order[1], rack_order[2], rack_order[3]], [],[numBasket[0], numBasket[1]], [numBasket[2], numBasket[3]], []])

    def numbers_button(self):

        self.p = self.balls.numbers_method(self.i)

        self.date = time.strftime("%d_%m_%Y")
        self.time = time.strftime("%H:%M:%S")

        numBasket = self.p[0]
        rack_order = self.p[1]

        #output to CSV file current setup
        resultFile = open(self.Name + "_" + self.date + ".csv", "a")
        writer = csv.writer(resultFile, dialect='excel', lineterminator='\n')

        writer.writerows([[],[str(self.time)], [rack_order[0], rack_order[1], rack_order[2], rack_order[3]], [],[numBasket[0], numBasket[1]], [numBasket[2], numBasket[3]], []])

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
    window = Mainwindow()

    palette = QPalette()
    palette.setColor(QPalette.Background, Qt.white)
    window.setPalette(palette)
    window.show()
    window.raise_()
    simulation.exec_()

if __name__ == "__main__":
    main()