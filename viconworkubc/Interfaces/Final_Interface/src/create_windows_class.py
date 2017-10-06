from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class Create_windows(QWidget):
    def __init__(self, balls):
        super().__init__()
        self.balls = balls

    # def letters_method(self, i):
    #     Llist = self.combi_letters[i]
    #     self.letters = []
    #
    #     for currPlot in Llist:
    #         self.letters.append(QPixmap(":/" + currPlot + ".png"))
    #
    #     pos_0 = self.letters[0]
    #     pos_1 = self.letters[1]
    #     pos_2 = self.letters[2]
    #     pos_3 = self.letters[3]  #.scaled(128, 128, Qt.KeepAspectRatio)
    #
    #     self.lcd0.setPixmap(pos_0)
    #     self.lcd1.setPixmap(pos_1)
    #     self.lcd2.setPixmap(pos_2)
    #     self.lcd3.setPixmap(pos_3)
    #
    #     self.number_balls = plot(Llist)
    #     return Llist
    #
    # def numbers_method(self,i):
    #
    #     rack_list = random.sample(self.combi1[i],4)
    #     basket_list = random.sample(self.combi2[i],4)
    #
    #     self.pos = []
    #
    #     for currPlot in self.number_balls:
    #         self.pos.append(QPixmap(":/" + currPlot + ".png"))
    #
    #     self.one.setPixmap(self.pos[basket_list[0]-1])
    #     self.two.setPixmap(self.pos[basket_list[1]-1])
    #     self.three.setPixmap(self.pos[basket_list[2]-1])
    #     self.four.setPixmap(self.pos[basket_list[3]-1])
    #
    #     self.rack0.setPixmap(self.pos[rack_list[0]-1].scaled(128, 128, Qt.KeepAspectRatio))
    #     self.rack1.setPixmap(self.pos[rack_list[1]-1].scaled(128, 128, Qt.KeepAspectRatio))
    #     self.rack2.setPixmap(self.pos[rack_list[2]-1].scaled(128, 128, Qt.KeepAspectRatio))
    #     self.rack3.setPixmap(self.pos[rack_list[3]-1].scaled(128, 128, Qt.KeepAspectRatio))
    #
    #     return [basket_list, rack_list]

    def fw_method(self,i,item):

        self.rack = self.combi1[i]
        color = self.colors

        if item ==0:
            self.fw_rack1.setPixmap(QPixmap(":/Black_ball.png").scaled(200, 200, Qt.KeepAspectRatio))  # Assign images to each label
            self.fw_rack2.setPixmap(QPixmap(":/Black_ball.png").scaled(200, 200, Qt.KeepAspectRatio))
            self.fw_rack3.setPixmap(QPixmap(":/Black_ball.png").scaled(200, 200, Qt.KeepAspectRatio))
            self.fw_rack4.setPixmap(QPixmap(":/Black_ball.png").scaled(200, 200, Qt.KeepAspectRatio))

        ## Reset Layout

        self.ball_a.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))  # Assign images to each label
        self.ball_b.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
        self.ball_c.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
        self.ball_d.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
        self.ball_e.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))




        #print(color)
        #print(self.rack)

        # selection of reach & position rack
        if color[item] == 'Orange':
            self.ball_a.setPixmap(QPixmap(":/s_Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
            if self.rack[item] == 1:
                self.fw_rack1.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 2:
                self.fw_rack2.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 3:
                self.fw_rack3.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            else:
                self.fw_rack4.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        elif color[item] == 'Blue':
            self.ball_b.setPixmap(QPixmap(":/s_Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
            if self.rack[item] == 1:
                self.fw_rack1.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 2:
                self.fw_rack2.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 3:
                self.fw_rack3.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            else:
                self.fw_rack4.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        elif color[item] == 'Red':
            self.ball_c.setPixmap(QPixmap(":/s_Red.png").scaled(200, 200, Qt.KeepAspectRatio))
            if self.rack[item] == 1:
                self.fw_rack1.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 2:
                self.fw_rack2.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 3:
                self.fw_rack3.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            else:
                self.fw_rack4.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        elif color[item] == 'Purple':
            self.ball_d.setPixmap(QPixmap(":/s_Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
            if self.rack[item] == 1:
                self.fw_rack1.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 2:
                self.fw_rack2.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 3:
                self.fw_rack3.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            else:
                self.fw_rack4.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        elif color[item] == 'Yellow':
            self.ball_e.setPixmap(QPixmap(":/s_Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
            if self.rack[item] == 1:
                self.fw_rack1.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 2:
                self.fw_rack2.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif self.rack[item] == 3:
                self.fw_rack3.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
            else:
                self.fw_rack4.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))

        if item > 0:  # Leave rack with color inside
            if color[item-1] == 'Orange':
                if self.rack[item-1] == 1:
                    self.fw_rack1.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 2:
                    self.fw_rack2.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 3:
                    self.fw_rack3.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
                else:
                    self.fw_rack4.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif color[item-1] == 'Blue':
                if self.rack[item-1] == 1:
                    self.fw_rack1.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 2:
                    self.fw_rack2.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 3:
                    self.fw_rack3.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
                else:
                    self.fw_rack4.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif color[item-1] == 'Red':
                if self.rack[item-1] == 1:
                    self.fw_rack1.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 2:
                    self.fw_rack2.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 3:
                    self.fw_rack3.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
                else:
                    self.fw_rack4.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif color[item-1] == 'Purple':

                if self.rack[item-1] == 1:
                    self.fw_rack1.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 2:
                    self.fw_rack2.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 3:
                    self.fw_rack3.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
                else:
                    self.fw_rack4.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
            elif color[item-1] == 'Yellow':
                if self.rack[item-1] == 1:
                    self.fw_rack1.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 2:
                    self.fw_rack2.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif self.rack[item-1] == 3:
                    self.fw_rack3.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
                else:
                    self.fw_rack4.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))

        if item == 3: # assign color into the rack of the second window
            j = 0
            for x in color:
                if x == 'Orange':
                    if self.rack[j] == 1:
                        self.sw_rack1.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 2:
                        self.sw_rack2.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 3:
                        self.sw_rack3.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
                    else:
                        self.sw_rack4.setPixmap(QPixmap(":/Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif x == 'Blue':
                    if self.rack[j] == 1:
                        self.sw_rack1.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 2:
                        self.sw_rack2.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 3:
                        self.sw_rack3.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
                    else:
                        self.sw_rack4.setPixmap(QPixmap(":/Blue.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif x == 'Red':
                    if self.rack[j] == 1:
                        self.sw_rack1.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 2:
                        self.sw_rack2.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 3:
                        self.sw_rack3.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
                    else:
                        self.sw_rack4.setPixmap(QPixmap(":/Red.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif x == 'Purple':
                    if self.rack[j] == 1:
                        self.sw_rack1.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 2:
                        self.sw_rack2.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 3:
                        self.sw_rack3.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
                    else:
                        self.sw_rack4.setPixmap(QPixmap(":/Purple.png").scaled(200, 200, Qt.KeepAspectRatio))
                elif x == 'Yellow':
                    if self.rack[j] == 1:
                        self.sw_rack1.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 2:
                        self.sw_rack2.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
                    elif self.rack[j] == 3:
                        self.sw_rack3.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
                    else:
                        self.sw_rack4.setPixmap(QPixmap(":/Yellow.png").scaled(200, 200, Qt.KeepAspectRatio))
                j = j+1
            k = 0
            for x in self.rack:
                self.posCol[x - 1] = self.colors[k]
                #print(self.posCol)
                k = k + 1

            self.colors = combi_letters()

            self.one.setPixmap(QPixmap(":/Black_ball.png").scaled(250, 250, Qt.KeepAspectRatio))  # Assign images to each label
            self.two.setPixmap(QPixmap(":/Black_ball.png").scaled(250, 250, Qt.KeepAspectRatio))
            self.three.setPixmap(QPixmap(":/Black_ball.png").scaled(250, 250, Qt.KeepAspectRatio))
            self.four.setPixmap(QPixmap(":/Black_ball.png").scaled(250, 250, Qt.KeepAspectRatio))

        elif i == 23:
            self.combi1 = combi()



    def sw_methods(self,j, item, sw_item):
        sw_rack = self.combi2[j] # position in the rack (Reach)
        basket_pos = self.combi3[j] # position in the basket(to drop the ball)

        # self.sw_rack1.setPixmap(QPixmap(":/"+ self.posCol[0] +".png").scaled(200, 200, Qt.KeepAspectRatio))
        # self.sw_rack2.setPixmap(QPixmap(":/" + self.posCol[1] + ".png").scaled(200, 200, Qt.KeepAspectRatio))
        # self.sw_rack3.setPixmap(QPixmap(":/" + self.posCol[2] + ".png").scaled(200, 200, Qt.KeepAspectRatio))
        # self.sw_rack4.setPixmap(QPixmap(":/" + self.posCol[3] + ".png").scaled(200, 200, Qt.KeepAspectRatio))



        posBasket = basket_pos[sw_item - 1]
        basketCol = self.posCol[sw_rack[sw_item-1]-1]

        # if basketCol == 'Orange':
        #     if sw_rack[sw_item] == 1 and posBasket == 1:
        #         self.sw_rack1.setPixmap(QPixmap(":/s_Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
        #         self.one.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        #     elif sw_rack[sw_item] == 2 and posBasket == 1:
        #             self.sw_rack1.setPixmap(QPixmap(":/s_Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
        #             self.one.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        #     elif sw_rack[sw_item] == 3 and posBasket == 1:
        #                 self.sw_rack1.setPixmap(QPixmap(":/s_Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
        #                 self.one.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        #     elif sw_rack[sw_item] == 4 and posBasket == 1:
        #                     self.sw_rack1.setPixmap(QPixmap(":/s_Orange.png").scaled(200, 200, Qt.KeepAspectRatio))
        #                     self.one.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        #         elif posBasket == 2:
        #             self.two.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        #         elif posBasket == 3:
        #             self.three.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))
        #         elif posBasket == 4:
        #             self.four.setPixmap(QPixmap(":/s_White.png").scaled(200, 200, Qt.KeepAspectRatio))

        if(posBasket == 1):
            self.one.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))
        elif posBasket == 2:
            self.two.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))
        elif posBasket == 3:
            self.three.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))
        elif posBasket == 4:
            self.four.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))



        # if(item == 0 and self.posCol[0] != 0):
        #     index = 0
        #
        #     basketCol = self.posCol[sw_rack[index]-1]
        #     posBasket = basket_pos[index]
        #     if posBasket == 1:
        #         self.one.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))
        #     elif posBasket == 2:
        #         self.two.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))
        #     elif posBasket == 3:
        #         self.three.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))
        #     elif posBasket == 4:
        #         self.four.setPixmap(QPixmap(":/" + basketCol +".png").scaled(250, 250, Qt.KeepAspectRatio))
        #
        #     index = index + 1







# def plot(color,rack,item):
#     if color[item] == 'A':
#         self.ball_a.setPixmap(QPixmap(":/Orange.png"))
#         if rack[item] == 1:
#             pos1 = 'Orange'
#         elif rack[item] == 2:
#             pos2 = 'Orange'
#         elif rack[item] == 3:
#             pos3 = 'Orange'
#         else:
#             pos4 = 'Orange'
#     elif color[item] == 'B':
#         if rack[item] == 1:
#             pos1 = 'Blue'
#         elif rack[item] == 2:
#             pos2 = 'Blue'
#         elif rack[item] == 3:
#             pos3 = 'Blue'
#         else:
#             pos4 = 'Blue'
#     elif color[item] == 'C':
#         if rack[item] == 1:
#             pos1 = 'Red'
#         elif rack[item] == 2:
#             pos2 = 'Red'
#         elif rack[item] == 3:
#             pos3 = 'Red'
#         else:
#             pos4 = 'Red'
#     elif color[item] == 'D':
#         if rack[item] == 1:
#             pos1 = 'Purple'
#         elif rack[item] == 2:
#             pos2 = 'Purple'
#         elif rack[item] == 3:
#             pos3 = 'Purple'
#         else:
#             pos4 = 'Purple'
#     elif color[item] == 'E':
#         if rack[item] == 1:
#             pos1 = 'Yellow'
#         elif rack[item] == 2:
#             pos2 = 'Yellow'
#         elif rack[item] == 3:
#             pos3 = 'Yellow'
#         else:
#             pos4 = 'Yellow'
#     item = item + 1
#     return [pos1, pos2, pos3, pos4]