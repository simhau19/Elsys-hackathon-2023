import serial
import json
import pygame


arduinoSerial = serial.Serial('COM6')

screen_width = 960
screen_height = 540

white = (255,255,255)
black = (0,0,0)



def main():
    pygame.init()
    screen = pygame.display.set_mode((screen_width, screen_height))
    servo_on = True
    button_color = (255,0,0)

    run = True
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                if screen_width/2 <= mouse[0] <= screen_width/2+100 and screen_height/2 <= mouse[1] <= screen_height/2+100:
                    servo_on =  not servo_on
                    print(str(int(servo_on)))
                    arduinoSerial.write( str(int(servo_on)).encode() )


        screen.fill((0,0,0))
        mouse = pygame.mouse.get_pos()

        if(servo_on): button_color = (255,0,0)
        else: button_color = (0,255,0)
        pygame.draw.rect(screen, button_color, [screen_width/2, screen_height/2, 100,100])

        if(arduinoSerial.in_waiting):
            text = arduinoSerial.readline().decode()
            try:
                data = json.loads(text)
                print("1:", data["loadcell_1"] , "\n2:", data["loadcell_2"])
            except:
                for char in text:
                    print(ord(char))

   
        pygame.display.update()

        
        

main()