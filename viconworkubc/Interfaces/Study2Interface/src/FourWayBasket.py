from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class FourWayBasket(QWidget):
    def __init__(self, icon_dict):
        super().__init__()

        self.icon_dict = icon_dict
        self.basket_icons = []
        self.basket_colors = ['black', 'black', 'black', 'black']
        self.basket_highlights = [False, False, False, False]

        self.frame_basket = QFrame()

        self.frame_basket.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_basket.setLineWidth(2)
        self.frame_basket.setMidLineWidth(3)
        self.frame_basket.setMinimumSize(300, 300)

        self.basket1 = QHBoxLayout()
        self.basket1.setAlignment(Qt.AlignCenter)

        self.basket2 = QHBoxLayout()
        self.basket2.setAlignment(Qt.AlignCenter)

        self.quadrants = []
        for i in range(0,5):
            curLabel = QLabel()
            self.quadrants.append(curLabel)
            curLabel.setPixmap(icon_dict.icon_dict["black"])

        self.basket1.addWidget(self.quadrants[0])
        self.basket1.addWidget(self.quadrants[1])
        self.basket2.addWidget(self.quadrants[2])
        self.basket2.addWidget(self.quadrants[3])

        self.basket = QVBoxLayout()
        self.basket.addLayout(self.basket1)
        self.basket.addLayout(self.basket2)

        self.frame_basket.setLayout(self.basket)

    def basket_window(self):
        return self.frame_basket

    def setBallColor(self, index, colorIndex):
        self.basket_colors[index] = self.icon_dict.ramp_pos[colorIndex]

    def setBallColorByName(self, index, colorName):
        self.basket_colors[index] = colorName

    def setAllBallsColor(self, colorIndex):
        cur_color = self.icon_dict.ramp_pos[colorIndex]
        for i in range(0,4):
            self.basket_colors[i] = cur_color

    def clearHighlights(self):
        self.basket_highlights = [False, False, False, False]

    def highLightBall(self, index):
        self.basket_highlights[index] = True

    def updateBallPixmaps(self):
        for i in range(0,4):
            cur_color = self.basket_colors[i]
            cur_dict = self.icon_dict.icon_dict_selected if self.basket_highlights[i] else self.icon_dict.icon_dict
            self.quadrants[i].setPixmap(cur_dict[cur_color])

