import time
import pygame
import os

pygame.init()

WIDTH=800
HEIGHT=600

screen = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("OpenCircuit Track Builder (2026.13.7)")

running=True

# Inits

camX = 0
camY = 0
zoom = 1
speed = 10
tileSize = 32

clock = pygame.time.Clock()


# Loop

while running:

    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            running=False
    
    # Inputs
    mx,my=pygame.mouse.get_pos()
    left,middle,right=pygame.mouse.get_pressed()
    keys=pygame.key.get_pressed()

    if keys[pygame.K_w]:
        camY-=speed
    if keys[pygame.K_s]:
        camY+=speed
    if keys[pygame.K_a]:
        camX-=speed
    if keys[pygame.K_d]:
        camX+=speed
    if keys[pygame.K_e]:
        zoom+=1
        time.sleep(0.1)
    if keys[pygame.K_q] and zoom > 1:
        zoom-=1
        time.sleep(0.1)


    # Calculations

    drawSize = tileSize*zoom
    startX =- (camX%drawSize)
    startY =- (camY%drawSize)

    # Draw
    screen.fill((30,30,30))

    for x in range(startX,WIDTH,drawSize):
        pygame.draw.line(screen,(55,55,55),(x,0),(x,HEIGHT))

    for y in range(startY,HEIGHT,drawSize):
        pygame.draw.line(screen,(55,55,55),(0,y),(WIDTH,y))

    pygame.display.flip()
    clock.tick(60)

pygame.quit()