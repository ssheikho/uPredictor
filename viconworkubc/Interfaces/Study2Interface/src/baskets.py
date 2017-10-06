from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys

from ToggleBasket import *

class Baskets(QWidget):
    def __init__(self, icon_dict):
        super().__init__()

        self.frame = QFrame()
        self.vbox = QVBoxLayout()
        self.vbox.setAlignment(Qt.AlignCenter)
        self.frame.setLayout(self.vbox)

        self.baskets = []
        for i in range(0, 3):
            self.baskets.append(ToggleBasket(icon_dict))
            self.vbox.addWidget(self.baskets[i].basket_window())

        self.baskets[0].setNBalls(1)
        self.baskets[1].setNBalls(4)
        self.baskets[2].setNBalls(1)

    def baskets_window(self):
        return self.frame

    def setOneBallBasket(self, index):
        self.baskets[0].setNBalls(4)
        self.baskets[1].setNBalls(4)
        self.baskets[2].setNBalls(4)
        self.baskets[index].setNBalls(1)

    def setBallColor(self, index, color_index):
        basketIndex = 0
        curIndex = index
        while curIndex >= self.baskets[basketIndex].getNBalls():
            curIndex -= self.baskets[basketIndex].getNBalls()
            basketIndex += 1
        self.baskets[basketIndex].setBallColor(curIndex, color_index)

    def setBallColorByName(self, index, colorName):
        basketIndex = 0
        curIndex = index
        while curIndex >= self.baskets[basketIndex].getNBalls():
            curIndex -= self.baskets[basketIndex].getNBalls()
            basketIndex += 1
        self.baskets[basketIndex].setBallColorByName(curIndex, colorName)

    def highLightBall(self, index):
        basketIndex = 0
        curIndex = index
        while curIndex >= self.baskets[basketIndex].getNBalls():
            curIndex -= self.baskets[basketIndex].getNBalls()
            basketIndex += 1
        self.baskets[basketIndex].highLightBall(curIndex)

    def clearHighlights(self):
        self.baskets[0].clearHighlights()
        self.baskets[1].clearHighlights()
        self.baskets[2].clearHighlights()

    def setAllBallsColor(self, colorIndex):
        self.baskets[0].setAllBallsColor(colorIndex)
        self.baskets[1].setAllBallsColor(colorIndex)
        self.baskets[2].setAllBallsColor(colorIndex)

    def updateBallPixmaps(self):
        self.baskets[0].updateBallPixmaps()
        self.baskets[1].updateBallPixmaps()
        self.baskets[2].updateBallPixmaps()