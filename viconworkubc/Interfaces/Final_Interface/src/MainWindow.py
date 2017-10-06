
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import csv
import datetime
import sys
import time
import resources2
from create_ball_class import *
from create_windows_class import *
from create_ramp_class import *
from create_rack_class import *
from create_basket_class import *
from create_icon_dict import *
from create_warning_box import *


class Mainwindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.nsteps = 14;

        self.metafile = open("metadata.txt", 'r')
        self.partno = int(self.metafile.readline()) + 1
        self.metafile.close()

        self.metafile = open("metadata.txt", 'w')
        self.metafile.write(str(self.partno))
        self.metafile.close()

        self.filename = "part_" + str(self.partno) + ".txt"
        self.file = open(self.filename, 'w');

        self.file.write("Participant #: %d \n" % (self.partno))
        self.file.write("Time #: %s  \n" % (datetime.datetime.now().__str__()))

        self.balls = Create_balls(self.nsteps)
        #self.balls.print_info()
        #self.current_step = 0;

        self.setWindowTitle("Caris Lab - University of British Columbia")
        self.icon_dict = Create_icon_dict()
        self.create_phase_1_window()
        self.showFullScreen()
        self.done = False
        self.nrounds = 25

    def create_phase_1_window(self):
        self.widget = QWidget()
        self.first_tab = QVBoxLayout()
        self.ramp_window = Create_ramp()
        self.rack_window_a = Create_rack()
        self.first_tab.addWidget(self.ramp_window.ramp_window(self.balls, self.icon_dict))
        self.first_tab.addSpacing(10)
        self.first_tab.addWidget(self.rack_window_a.rack_window(self.balls, self.icon_dict))
        self.widget.setLayout(self.first_tab)
        self.setCentralWidget(self.widget)


    def create_phase_2_window(self):
        self.widget = QWidget()
        self.second_tab = QVBoxLayout()
        self.rack_window_b = Create_rack()
        self.basket = Create_basket(self.balls)
        self.setCentralWidget(self.widget)
        self.second_tab.addWidget(self.rack_window_b.rack_window(self.balls, self.icon_dict))
        self.second_tab.addSpacing(10)
        self.second_tab.addWidget(self.basket.basket_window(self.balls, self.icon_dict))
        self.widget.setLayout(self.second_tab)

    def create_phase_3_window(self, text):
        self.widget = QWidget()
        self.second_tab = QVBoxLayout()
        self.warning_box = Create_warning_box()
        self.basket = Create_basket(self.balls)
        self.setCentralWidget(self.widget)
        self.second_tab.addWidget(self.warning_box.warning_box(text))
        self.widget.setLayout(self.second_tab)

    def keyPressEvent(self, event):
        if(type(event)==QKeyEvent):
            key = event.key()
            # print("Step %d" % (self.balls.current_step))
            # print("Done %d" % (self.done))
            if((key == Qt.Key_Space) and (self.done == False)):
                self.balls.current_step = (self.balls.current_step + 1) % self.nsteps
                thetime = time.time().__str__()
                self.file.write("+ " + self.balls.current_step.__str__() + "  " + thetime + "\n")
                self.balls.finaltime[self.balls.current_step] = thetime
            if(key == Qt.Key_Backspace):
                self.done = False
                if(self.balls.current_step > 0):
                    self.balls.current_step = (self.balls.current_step - 1) % self.nsteps
                thetime = time.time().__str__()
                self.file.write("- " + self.balls.current_step.__str__() + "  " + thetime + "\n")
                self.balls.finaltime[self.balls.current_step] = thetime
            if(key == Qt.Key_Escape):
                self.balls.endroll(self.file)
                self.close()

        if(self.balls.current_step == 13):
            if(self.balls.n_rounds < self.nrounds):
                self.balls.endroll(self.file)
                self.balls.reroll(self.file)
                self.balls.current_step = 0

        if(self.balls.current_step <= 5):
            self.create_phase_1_window()
        elif(self.balls.current_step < 12):
            self.create_phase_2_window()
        else:
            if self.balls.n_rounds == self.nrounds:
                self.create_phase_3_window("Done!")
                self.done = True
            else:
                self.create_phase_3_window("Proceed to round " + (self.balls.n_rounds + 1).__str__() + "?")


    def initialDialog(self):

        msg = QDialog()
        msg.setWindowTitle("Participant Information")

        grid = QGridLayout()
        msg.setLayout(grid)

        msg.setMinimumHeight(100)
        msg.setMinimumWidth(200)

        nameLabel = QLabel("Participant ID #:", msg)
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