import serial
import json
import pygame
import time
import math


arduinoSerial = serial.Serial('COM6')

screen_width = 960
screen_height = 540

white = (255,255,255)
black = (0,0,0)

movement_treshold = 600
time_treshold = 8



def main():
    pygame.init()
    screen = pygame.display.set_mode((screen_width, screen_height))
    servo_on = True
    button_color = (255,0,0)

    old_scale = 0
    timer = time.time()

    font = pygame.font.SysFont('arial', 30)
    olga_text = font.render( "Liggesår alert!!! Olga må flyttes!", True, (255,255,255) )
    olga_rect = olga_text.get_rect()

    


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
            
            try:
                raw_text = arduinoSerial.readline().decode()
                data = json.loads(raw_text)
                #print("1:", data["loadcell_1"] , "\n2:", data["loadcell_2"])
                scale = int(data["loadcell_2"])
                difference = scale - old_scale
                if(abs(difference) > movement_treshold):
                    old_scale = scale
                    timer = time.time()
                    print("reset")
                    
                
                
            except:
                None

        
        if(time.time() - timer > time_treshold):
            screen.blit(olga_text, olga_rect)

        pygame.display.update()

        
        

main()