from balls import *

from PyQt4.QtCore import *
from PyQt4.QtGui import *

class StudyTwoLogic:
    def __init__(self, rampWindow, rackWindowA, rackWindowB, baskets, warningA, warningB
                 , leftWindow, rightWindow, windowContainer):
        super().__init__()

        metafile = open("metadata.txt", 'r')
        partno = int(metafile.readline()) + 1
        metafile.close()

        metafile = open("metadata.txt", 'w')
        metafile.write(str(partno))
        metafile.close()

        self.rampWindow = rampWindow
        self.rackWindowA = rackWindowA
        self.rackWindowB = rackWindowB
        self.baskets = baskets
        self.warningA = warningA
        self.warningB = warningB
        self.escapeWarningLevel = 0

        self.leftWindow = leftWindow
        self.rightWindow = rightWindow

        self.windowContainer = windowContainer

        self.balls = Balls(partno, 4, 12)

        self.renderStep(self.balls.task_step)

    def renderStep(self, step):
        if self.escapeWarningLevel == 1:
            self.rampWindow.ramp_window().hide()
            self.rackWindowA.rack_window().hide()
            self.rackWindowB.rack_window().hide()
            self.baskets.baskets_window().hide()
            self.warningA.setWarningText("Escape Pressed")
            self.warningB.setWarningText("Hit Escape Again to Exit")
            self.warningA.warning_box().show()
            self.warningB.warning_box().show()

        elif self.escapeWarningLevel == 2:
            self.rampWindow.ramp_window().hide()
            self.rackWindowA.rack_window().hide()
            self.rackWindowB.rack_window().hide()
            self.baskets.baskets_window().hide()
            self.warningA.setWarningText("Are You Sure?")
            self.warningB.setWarningText("Hit Escape Again to Exit")
            self.warningA.warning_box().show()
            self.warningB.warning_box().show()

        elif self.balls.gameDone():
            self.rampWindow.ramp_window().hide()
            self.rackWindowA.rack_window().hide()
            self.rackWindowB.rack_window().hide()
            self.baskets.baskets_window().hide()
            self.warningA.setWarningText("Task Complete")
            self.warningB.setWarningText("Hit Escape to Exit")
            self.warningA.warning_box().show()
            self.warningB.warning_box().show()

        else:
            self.baskets.setOneBallBasket(self.balls.one_ball_basket)

            self.rampWindow.clearHighlights()
            self.rackWindowA.clearHighlights()
            self.rackWindowB.clearHighlights()
            self.rackWindowA.clearBallColors()
            self.rackWindowB.clearBallColors()
            self.baskets.setAllBallsColor(5)
            self.baskets.clearHighlights()

            #Step zero, show the screen all nice and clear

            #Highlight the ball to be picked up from the first rack
            if (step > 0) & (step < 10):
                self.rackWindowA.highlightBall(self.balls.to_rack[step - 1])
                self.rackWindowB.highlightBall(self.balls.to_rack[step - 1])

            #From steps 2-9, fill in the colored balls in the rack
            if step > 1:
                endrange = step - 1 if step < 10 else 9
                for i in range(0, endrange):
                    self.rackWindowA.setBallColor(self.balls.to_rack[i], self.balls.from_ramp[i])
                    self.rackWindowB.setBallColor(self.balls.to_rack[i], self.balls.from_ramp[i])

            #From steps 2-9 highlight the ball that's intended to be filled in on the rack
            stepMinusTwelve = step - 12
            if (step > 11) & (step < 21):
                self.rackWindowA.highlightBall(self.balls.from_rack[stepMinusTwelve])
                self.rackWindowB.highlightBall(self.balls.from_rack[stepMinusTwelve])

            #As the balls are removed from the rack (Step 13+), set the rack back to black
            if step > 12:
                endRange = 9 if step > 21 else step - 12
                for i in range(0, endRange):
                    ball_color = self.rackWindowA.getBallColor(self.balls.from_rack[i])
                    self.rackWindowA.setBallColor(self.balls.from_rack[i], 5)
                    self.rackWindowB.setBallColor(self.balls.from_rack[i], 5)
                    #Also, you should totes fill in the baskets
                    self.baskets.setBallColorByName(self.balls.to_basket[i], ball_color)

            if (step >= 12) & (step < 21):
                self.baskets.highLightBall(self.balls.to_basket[step - 12])

            #Render all of that stuff that you did
            self.rackWindowA.updateBallPixmaps()
            self.rackWindowB.updateBallPixmaps()
            self.baskets.updateBallPixmaps()

            #Swap around the interface so the Ramp, Rack, or Baskets are showing in the correct location
            if step == 0:
                self.rampWindow.ramp_window().show()
                self.rackWindowA.rack_window().hide()
                self.rackWindowB.rack_window().show()
                self.baskets.baskets_window().hide()
                self.warningA.warning_box().hide()
                self.warningB.warning_box().hide()

            elif step < 10:
                self.rampWindow.highlightBall(self.balls.from_ramp[step - 1])

                self.rampWindow.ramp_window().show()
                self.rackWindowA.rack_window().hide()
                self.rackWindowB.rack_window().show()
                self.baskets.baskets_window().hide()
                self.warningA.warning_box().hide()
                self.warningB.warning_box().hide()

            elif step < 11:
                self.rampWindow.ramp_window().show()
                self.rackWindowA.rack_window().hide()
                self.rackWindowB.rack_window().show()
                self.baskets.baskets_window().hide()
                self.warningA.warning_box().hide()
                self.warningB.warning_box().hide()

            elif step < 22:
                self.rampWindow.ramp_window().hide()
                self.rackWindowA.rack_window().show()
                self.rackWindowB.rack_window().hide()
                self.baskets.baskets_window().show()
                self.warningA.warning_box().hide()
                self.warningB.warning_box().hide()

            else:
                self.rampWindow.ramp_window().hide()
                self.rackWindowA.rack_window().hide()
                self.rackWindowB.rack_window().hide()
                self.baskets.baskets_window().hide()
                self.warningA.setWarningText("Proceed to Round: " + str(self.balls.current_round + 2) + "?")
                self.warningB.setWarningText("Hit Enter")
                self.warningA.warning_box().show()
                self.warningB.warning_box().show()

    def keyPressEvent(self, event):
        if type(event) == QKeyEvent:
            key = event.key()
            if key == Qt.Key_Space:
                if self.escapeWarningLevel == 0:
                    self.balls.nextStep()
            if key == Qt.Key_Backspace:
                if self.escapeWarningLevel == 0:
                    self.balls.backStep()
                else:
                    self.escapeWarningLevel = 0
            if (key == Qt.Key_Return) | (key == Qt.Key_Enter):
                if self.balls.thisIsTheFinalRound() == False:
                    self.balls.nextRound()
            if (key == Qt.Key_Escape):
                if self.balls.gameDone():
                    self.balls.endroll()
                    self.windowContainer.closeAll()
                elif self.escapeWarningLevel == 2:
                    self.balls.endroll()
                    self.windowContainer.closeAll()
                else:
                    self.escapeWarningLevel += 1
            self.renderStep(self.balls.task_step)
                # print("%d" % self.task_step)