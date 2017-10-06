from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class Ramp(QWidget):
    def __init__(self, icon_dict):
        super().__init__()

        self.icon_dict = icon_dict

        self.ballHighlights = [False, False, False, False, False]

        self.ramp_frame = QFrame()             # Create frame to contain layout related to the rack with 5 balls

        self.ramp_frame.setFrameStyle(QFrame.Box | QFrame.Raised)      # Define frame appearance
        self.ramp_frame.setLineWidth(2)
        self.ramp_frame.setMidLineWidth(3)
        self.ramp_frame.setMinimumSize(600, 420)

        self.balls_row = QHBoxLayout()              # Create horizontal layout to contain pictures of the balls
        self.letbox = QHBoxLayout()                 # Create HLayout to contain pictures of letters asociate to each ball
        self.balls_row.setAlignment(Qt.AlignCenter)
        self.letbox.setAlignment(Qt.AlignCenter)

        self.ball_labels = []
        self.letterbox_labels = []
        for i in range(0,5):
            curBallLabel = QLabel()
            curLetterboxLabel = QLabel()
            self.ball_labels.append(curBallLabel)
            self.letterbox_labels.append(curLetterboxLabel)
            self.balls_row.addWidget(curBallLabel)       # add widgets to the HLayout
            self.letbox.addWidget(curLetterboxLabel) # add widgets to the HLayout

        self.updateBallPixmaps()

        self.letterbox_labels[0].setPixmap(icon_dict.icon_dict["black_a"])
        self.letterbox_labels[1].setPixmap(icon_dict.icon_dict["black_b"])
        self.letterbox_labels[2].setPixmap(icon_dict.icon_dict["black_c"])
        self.letterbox_labels[3].setPixmap(icon_dict.icon_dict["black_d"])
        self.letterbox_labels[4].setPixmap(icon_dict.icon_dict["black_e"])

        self.firstWindow1 = QVBoxLayout()               # Create a vertical Layout to contain both QLayouts
        self.firstWindow1.setAlignment(Qt.AlignCenter)
        self.firstWindow1.addLayout(self.balls_row)
        self.firstWindow1.addLayout(self.letbox)

        self.ramp_frame.setLayout(self.firstWindow1)       # Assign VLayout to the frame

    def clearHighlights(self):
        self.ballHighlights = [False, False, False, False, False]
        self.updateBallPixmaps()

    def highlightBall(self, index):
        self.ballHighlights[index] = True
        self.updateBallPixmaps()

    def updateBallPixmaps(self):
        # Assign images to each label
        for i in range(0,5):
            ramp_pos = self.icon_dict.ramp_pos[i]
            cur_dict = self.icon_dict.icon_dict_selected if  self.ballHighlights[i] else self.icon_dict.icon_dict
            cur_icon = cur_dict[ramp_pos]
            self.ball_labels[i].setPixmap(cur_icon)


    def ramp_window(self):
        return self.ramp_frame     # return frame (widget)