import sys
sys.path.append("../../build/")

from time import sleep
import libfishbot as fishbot

print(fishbot.version())

fishbot = fishbot.FishBot()
fishbot.set_protocol_serial('/dev/ttyUSB0',115200)
fishbot.set_motion_model_diff2(0.170,3293,0.065 / 2)
fishbot.init()
sleep(1)
fishbot.update_protocol_config_uart(115200)
# fishbot.update_protocol_config_udp_server(3474)
sleep(0.5)
fishbot.restart()
sleep(2)

fishbot.destory()
