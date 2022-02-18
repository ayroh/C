&emsp;&emsp;TERM PROJECT
    
    Creates eps file including traditional geometric art according to Hankin's Method.
    Takes background and foreground color, tile size, angle offset, canvas size, archetype, and filename.
    If there aren't enough information, it takes info from default.txt
    
![image](https://user-images.githubusercontent.com/76924597/154773254-60c1bcc6-cf41-437e-8d43-674ae6161706.png)


    Here 4 examples respectively:
      background_color:(128,128,128),foreground_color:(255,0,0), tile_size:100,angle_offset:(45,10), canvas_size:(1000,1000), show_grid:True, archetype:Square, file_name:sq1.eps archetype:Hexagon, canvas_size:(600,600),file_name:hex2.eps
      background_color:(128,128,128),foreground_color:(255,0,0) tile_size:100, canvas_size:(1000,1000), show_grid:True, file_name:sqs.eps // Should produce an error because there is no described archetype.
      pattern_thickness:8,foreground_color:(0,127,55),archetype:Square,angle_offset:(24,5), file_name:def.eps  // This is a valid description because it contains mandatory fields file_name and archetype
      pattern_thickness:8,tile_size:80,canvas_size:(800,800),foreground_color:(0,127,55),angle_offset:(32,6),archetype:Hexagon, file_name:def2.eps  

![image](https://user-images.githubusercontent.com/76924597/154772989-6dadd9f0-9f1e-492f-b33d-bd727b5e8547.png)
![image](https://user-images.githubusercontent.com/76924597/154773038-ead88bad-ab86-43fd-8c89-3558d99387d4.png)

![image](https://user-images.githubusercontent.com/76924597/154773062-8965d23d-86ed-4d88-b582-6e915dda7ffe.png)
![image](https://user-images.githubusercontent.com/76924597/154773086-a58a8da3-86d4-474d-a744-3c30866b8e5e.png)
