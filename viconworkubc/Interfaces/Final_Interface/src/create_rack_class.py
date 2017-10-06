from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class Create_rack(QWidget):
    def __init__(self):
        super().__init__()

    def rack_window(self, balls, icon_dict):
        self.fw_frame_rack = QFrame()

        self.fw_frame_rack.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.fw_frame_rack.setLineWidth(2)
        self.fw_frame_rack.setMidLineWidth(3)
        self.fw_frame_rack.setMinimumSize(600, 420)

        self.fw_rack = QHBoxLayout()
        self.fw_rack.setAlignment(Qt.AlignCenter)
        self.fw_numbox = QHBoxLayout()  # Create HLayout to contain pictures of numbers asociate to the rack
        self.fw_numbox.setAlignment(Qt.AlignCenter)

        self.rack_labels = []
        self.numbox_labels = []
        for i in range(0,4):
            curRackLabel = QLabel()
            curNumberboxLabel = QLabel()
            self.rack_labels.append(curRackLabel)
            self.numbox_labels.append(curNumberboxLabel)
            self.fw_rack.addWidget(curRackLabel)       # add widgets to the HLayout
            self.fw_numbox.addWidget(curNumberboxLabel) # add widgets to the HLayout

        rack_icons = []
        for i in range(0,4):
            rack_icons.append((icon_dict.icon_dict["black"]))

        end_step = balls.current_step if balls.current_step < 5 else 4

        for i in range(0,end_step):
            rack_icon_string = "black"
            cur_dict = icon_dict.icon_dict
            from_ramp_slot = balls.from_ramp[i]
            to_rack_slot = balls.to_rack[i]
            rack_icon_string = icon_dict.ramp_pos[from_ramp_slot]

            if balls.current_step - 1 == i:
                cur_dict = icon_dict.icon_dict_selected

            if balls.current_step - 7 == i:
                cur_dict = icon_dict.icon_dict_selected

            rack_icons[to_rack_slot] = cur_dict[rack_icon_string]

        for i in range(0,4):
            self.rack_labels[i].setPixmap(rack_icons[i])

        self.numbox_labels[0].setPixmap(icon_dict.icon_dict["1"])  # Assign images to each label
        self.numbox_labels[1].setPixmap(icon_dict.icon_dict["2"])
        self.numbox_labels[2].setPixmap(icon_dict.icon_dict["3"])
        self.numbox_labels[3].setPixmap(icon_dict.icon_dict["4"])


        self.firstWindow2 = QVBoxLayout()  # Create a vertical Layout to contain both QLayouts
        self.firstWindow2.setAlignment(Qt.AlignCenter)
        self.firstWindow2.addLayout(self.fw_rack)
        self.firstWindow2.addLayout(self.fw_numbox)

        self.fw_frame_rack.setLayout(self.firstWindow2)  # Assign VLayout to the frame

        return self.fw_frame_rack