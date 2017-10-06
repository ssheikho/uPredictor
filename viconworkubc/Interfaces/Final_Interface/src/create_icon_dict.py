from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class Create_icon_dict():
    def __init__(self):
        super().__init__()

        self.ramp_pos = []
        self.ramp_pos.append('orange')
        self.ramp_pos.append('blue')
        self.ramp_pos.append('red')
        self.ramp_pos.append('purple')
        self.ramp_pos.append('yellow')

        self.icon_dict = {
            'black' : QPixmap(":/Black_ball.png").scaled(200, 200, Qt.KeepAspectRatio),

            'orange' : QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio),
            'blue' : QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio),
            'red' : QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio),
            'purple' : QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio),
            'yellow' : QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio),

            'black_a' : QPixmap(":/Black_A.png").scaled(200, 200, Qt.KeepAspectRatio),
            'black_b' : QPixmap(":/Black_B.png").scaled(200, 200, Qt.KeepAspectRatio),
            'black_c' : QPixmap(":/Black_C.png").scaled(200, 200, Qt.KeepAspectRatio),
            'black_d' : QPixmap(":/Black_D.png").scaled(200, 200, Qt.KeepAspectRatio),
            'black_e' : QPixmap(":/Black_E.png").scaled(200, 200, Qt.KeepAspectRatio),

            '1' : QPixmap(":/1.png").scaled(200, 200, Qt.KeepAspectRatio),
            '2' : QPixmap(":/2.png").scaled(200, 200, Qt.KeepAspectRatio),
            '3' : QPixmap(":/3.png").scaled(200, 200, Qt.KeepAspectRatio),
            '4' : QPixmap(":/4.png").scaled(200, 200, Qt.KeepAspectRatio),
        }

        self.icon_dict_selected = {
            'black' : QPixmap(":/Selected_White.png").scaled(200, 200, Qt.KeepAspectRatio),

            'orange' : QPixmap(":/Selected_Orange.png").scaled(200, 200, Qt.KeepAspectRatio),
            'blue' : QPixmap(":/Selected_Blue.png").scaled(200, 200, Qt.KeepAspectRatio),
            'red' : QPixmap(":/Selected_Red.png").scaled(200, 200, Qt.KeepAspectRatio),
            'purple' : QPixmap(":/Selected_Purple.png").scaled(200, 200, Qt.KeepAspectRatio),
            'yellow' : QPixmap(":/Selected_Yellow.png").scaled(200, 200, Qt.KeepAspectRatio)
        }