from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys

class OneWayBasket(QWidget):
    def __init__(self, icon_dict):
        super().__init__()

        self.icon_dict = icon_dict

        self.basket_icons = []
        self.basket_colors = ['black']
        self.basket_highlights = [False]

        self.frame_basket = QFrame()

        self.frame_basket.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_basket.setLineWidth(2)
        self.frame_basket.setMidLineWidth(3)
        self.frame_basket.setMinimumSize(326, 326)

        self.label = QLabel()
        self.label.setPixmap(icon_dict.solo_icon_dict["black"])
        self.basket = QVBoxLayout()
        self.basket.setAlignment(Qt.AlignCenter)
        self.basket.addWidget(self.label)

        self.frame_basket.setLayout(self.basket)

    def basket_window(self):
        return self.frame_basket

    def setBallColor(self, index, colorIndex):
        self.basket_colors[index] = self.icon_dict.ramp_pos[colorIndex]

    def setBallColorByName(self, index, colorName):
        self.basket_colors[index] = colorName

    def setAllBallsColor(self, colorIndex):
        self.basket_colors[0] = self.icon_dict.ramp_pos[colorIndex]

    def clearHighlights(self):
        self.basket_highlights = [False]

    def highLightBall(self, index):
        self.basket_highlights[index] = True

    def updateBallPixmaps(self):
        cur_color = self.basket_colors[0]
        cur_dict = self.icon_dict.icon_dict_selected if self.basket_highlights[0] else self.icon_dict.icon_dict
        # print(cur_color)
        self.label.setPixmap(cur_dict[cur_color])