from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys

from OneWayBasket import *
from FourWayBasket import *

class ToggleBasket(QWidget):
    def __init__(self, icon_dict):
        super().__init__()

        self.nballs = 4

        self.one_way_basket = OneWayBasket(icon_dict)
        self.four_way_basket = FourWayBasket(icon_dict)

        self.frame_basket = QFrame()

        self.frame_basket.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_basket.setLineWidth(2)
        self.frame_basket.setMidLineWidth(3)
        self.frame_basket.setMinimumSize(300, 300)

        self.basket = QVBoxLayout()
        self.basket.setAlignment(Qt.AlignCenter)
        self.frame_basket.setLayout(self.basket)
        self.basket.addWidget(self.one_way_basket.basket_window())
        self.basket.addWidget(self.four_way_basket.basket_window())
        self.one_way_basket.basket_window().hide()

    def basket_window(self):
        return self.frame_basket

    def setNBalls(self, nballs):
        if((nballs == 1) & (self.nballs == 4)):
            self.four_way_basket.basket_window().hide()
            self.one_way_basket.basket_window().show()
        elif((nballs == 4) & (self.nballs == 1)):
            self.one_way_basket.basket_window().hide()
            self.four_way_basket.basket_window().show()
        self.nballs = nballs

    def getNBalls(self):
        return self.nballs

    def setBallColor(self, index, colorIndex):
        if(self.nballs == 1):
            self.one_way_basket.setBallColor(index, colorIndex)
        elif(self.nballs == 4):
            self.four_way_basket.setBallColor(index, colorIndex)

    def setBallColorByName(self, index, colorName):
        if(self.nballs == 1):
            self.one_way_basket.setBallColorByName(index, colorName)
        elif(self.nballs == 4):
            self.four_way_basket.setBallColorByName(index, colorName)

    def setAllBallsColor(self, colorIndex):
        self.one_way_basket.setAllBallsColor(colorIndex)
        self.four_way_basket.setAllBallsColor(colorIndex)

    def clearHighlights(self):
        self.one_way_basket.clearHighlights()
        self.four_way_basket.clearHighlights()

    def highLightBall(self, index):
        if(self.nballs == 1):
            self.one_way_basket.highLightBall(index)
        elif(self.nballs == 4):
            self.four_way_basket.highLightBall(index)

    def updateBallPixmaps(self):
        self.one_way_basket.updateBallPixmaps()
        self.four_way_basket.updateBallPixmaps()

