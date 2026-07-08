import time
import pygame
import os

pygame.init()

screen = pygame.display.set_mode((800,600))
pygame.display.set_caption("OpenCircuit Track Builder (2026.8.7)")

running=True

while running:

    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            running=False
    
    # Inputs
    mx,my=pygame.mouse.get_pos()
    left,middle,right=pygame.mouse.get_pressed()
    keys=pygame.key.get_pressed()

    # Calculations

    # Draw
    screen.fill((30,30,30))
    pygame.draw.rect(screen,(255,255,255),(100,100,64,64))

    for x in range(0,800,32):
        pygame.draw.line(screen,(60,60,60),(x,0),(x,600))

    for y in range(0,600,32):
        pygame.draw.line(screen,(60,60,60),(0,y),(800,y))

    pygame.display.flip()

pygame.quit()
