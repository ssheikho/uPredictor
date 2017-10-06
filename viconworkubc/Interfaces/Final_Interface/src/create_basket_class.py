from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class Create_basket(QWidget):
    def __init__(self, balls):
        super().__init__()
        self.balls = balls

    def basket_window(self, balls, icon_dict):

        self.frame_basket = QFrame()

        self.frame_basket.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_basket.setLineWidth(2)
        self.frame_basket.setMidLineWidth(3)
        self.frame_basket.setMinimumSize(650, 500)

        self.basket1 = QHBoxLayout()
        self.basket1.setAlignment(Qt.AlignCenter)

        self.basket2 = QHBoxLayout()
        self.basket2.setAlignment(Qt.AlignCenter)

        self.quadrants = [];
        for i in range(0,5):
            curLabel = QLabel()
            self.quadrants.append(curLabel)

        self.basket1.addWidget(self.quadrants[0])
        self.basket1.addWidget(self.quadrants[1])
        self.basket2.addWidget(self.quadrants[2])
        self.basket2.addWidget(self.quadrants[3])

        basket_icons = []
        for i in range(0,4):
            basket_icons.append((icon_dict.icon_dict["black"]))

        end_step = balls.current_step if balls.current_step < 5 else 4

        for i in range(0,end_step):
            rack_icon_string = "black"
            cur_dict = icon_dict.icon_dict
            from_ramp_slot = balls.from_ramp[i]
            to_rack_slot = balls.to_rack[i]

            if balls.current_step < 6:
                rack_icon_string = icon_dict.ramp_pos[from_ramp_slot]

                if balls.current_step - 1 == i:
                    cur_dict = icon_dict.icon_dict_selected

            else:
                if balls.current_step - 7 >= i:
                    rack_icon_string = icon_dict.ramp_pos[from_ramp_slot]
                if balls.current_step - 7 == i:
                    cur_dict = icon_dict.icon_dict_selected

            basket_icons[to_rack_slot] = cur_dict[rack_icon_string]

        for i in range(0,4):
            self.quadrants[i].setPixmap(basket_icons[i])

        self.basket = QVBoxLayout()
        self.basket.addLayout(self.basket1)
        self.basket.addLayout(self.basket2)

        self.frame_basket.setLayout(self.basket)

        return self.frame_basket