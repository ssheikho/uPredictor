from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class IconDict():
    def __init__(self, size_index):
        super().__init__()

        self.ramp_pos = []
        self.ramp_pos.append('orange')
        self.ramp_pos.append('blue')
        self.ramp_pos.append('red')
        self.ramp_pos.append('purple')
        self.ramp_pos.append('yellow')
        self.ramp_pos.append('black')
        self.numbers = ['0', '1', '2', '3', '4']
        self.letters = ['black_a', 'black_b', 'black_c', 'black_d', 'black_e']

        if size_index == 0:
            scale = 200
        elif size_index == 1:
            scale = 150

        self.icon_dict = {
            'black' : QPixmap(":/Black_ball.png").scaled(scale, scale, Qt.KeepAspectRatio),

            'orange' : QPixmap(":/Orange.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'blue' : QPixmap(":/Blue.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'red' : QPixmap(":/Red.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'purple' : QPixmap(":/Purple.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'yellow' : QPixmap(":/Yellow.png").scaled(scale, scale, Qt.KeepAspectRatio),

            'black_a' : QPixmap(":/Black_A.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'black_b' : QPixmap(":/Black_B.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'black_c' : QPixmap(":/Black_C.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'black_d' : QPixmap(":/Black_D.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'black_e' : QPixmap(":/Black_E.png").scaled(scale, scale, Qt.KeepAspectRatio),

            '1' : QPixmap(":/1.png").scaled(scale, scale, Qt.KeepAspectRatio),
            '2' : QPixmap(":/2.png").scaled(scale, scale, Qt.KeepAspectRatio),
            '3' : QPixmap(":/3.png").scaled(scale, scale, Qt.KeepAspectRatio),
            '4' : QPixmap(":/4.png").scaled(scale, scale, Qt.KeepAspectRatio),

            'box' : QPixmap(":/box.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'box_white' : QPixmap(":/box_white.png").scaled(scale, scale, Qt.KeepAspectRatio),
        }

        self.solo_icon_dict = {
            'black' : QPixmap(":/Black_ball.png").scaled(scale, scale, Qt.KeepAspectRatio),

            'orange' : QPixmap(":/Solo_Orange.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'blue' : QPixmap(":/Solo_Blue.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'red' : QPixmap(":/Solo_Red.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'purple' : QPixmap(":/Solo_Purple.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'yellow' : QPixmap(":/Solo_Yellow.png").scaled(scale, scale, Qt.KeepAspectRatio)
        }

        self.solo_icon_dict_selected = {
            'orange' : QPixmap(":/Selected_Solo_Orange.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'blue' : QPixmap(":/Selected_Solo_Blue.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'red' : QPixmap(":/Selected_Solo_Red.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'purple' : QPixmap(":/Selected_Solo_Purple.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'yellow' : QPixmap(":/Selected_Solo_Yellow.png").scaled(scale, scale, Qt.KeepAspectRatio)
        }

        self.icon_dict_selected = {
            'black' : QPixmap(":/Selected_Black.png").scaled(scale, scale, Qt.KeepAspectRatio),

            'orange' : QPixmap(":/Selected_Orange.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'blue' : QPixmap(":/Selected_Blue.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'red' : QPixmap(":/Selected_Red.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'purple' : QPixmap(":/Selected_Purple.png").scaled(scale, scale, Qt.KeepAspectRatio),
            'yellow' : QPixmap(":/Selected_Yellow.png").scaled(scale, scale, Qt.KeepAspectRatio)
        }
