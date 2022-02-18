# C
My C Projects for CSE102 Lecture

&emsp;&emsp;PROJECT 1
  
    1901042643.c => 1.Finds roots of quadratic equation if equation has real roots according to inputs.
                    2.Finds newtonian root according to inputs.
                    3.Finds the closest multiple of the second number to the first number.


&emsp;&emsp;PROJECT 2
                
    1901042643_part1.c => 1.Finds if that triangle is drawnable according to triangle inequality theorem.
                          2.Finds type of that triangle(Equilateral, Isosceles or Scalene).
                          3.Finds perimeter and area of that triangle.
                      
    1901042643_part2.c => 1.Finds how many digits that input number has.
                          2.Finds nth digit of this number, when your number written 100 times next to each other.
                    
    1901042643_part3.c => Exchange Turkish Lira to Euro or Dollar according to your money.


&emsp;&emsp;PROJECT 3

    1901042643_part1.c => Sums or multiplicates, odd or even numbers until given input.

    1901042643_part2.c => Finds whether number is prime and if not why, until input is reached.

    1901042643_part3.c => Takes 2 integers, converts them to binary and if they have same length ANDs them.


&emsp;&emsp;PROJECT 4

    1901042643.c => Encrypts and decrypts messages according to function(is in pdf file).


&emsp;&emsp;PROJECT 5

    1901042643.c => 1.Reads news from file and records to another file that if that news is read.
                    2.Lists all read news.
                    3.Encrypts information from news according to functions(is in pdf file).
                

&emsp;&emsp;PROJECT 6

    1901042643.c => 1.Reads various words from file.
                    2.Stores 10 of them randomly.
                    3.Place them randomly at 8 directions to 20x20 grid.
                    4.Place random letters to empty places.
                    5.If player enters correct answer (t12 combative etc.) uppercase that word.
                
    6hileli.c => Cheated version of game for presentation.                
           
![image](https://user-images.githubusercontent.com/76924597/154772583-a92eabef-680f-4587-b38f-486ed509fcac.png)

![image](https://user-images.githubusercontent.com/76924597/154772622-730a40b2-9ac7-49b1-b461-c29f5ae9323a.png)

&emsp;&emsp;PROJECT 7

    1901042643.c => 1.Reads various games from file.
                    2.Lists Genres, Platforms, Years.
                    3.All information of a single game.
                    4.Average of the User Scores
                    5.Georographical Information of a Single Game
                    6.Frequence of the Genres
                    7.Frequence of the Platforms
                

&emsp;&emsp;PROJECT 8

    1901042643.c => Part 1: 1.Fill array: The option takes an integer number (n) from the user and fills the array with first n items of the Hofstadter's Q-Sequence.
                            2.Find biggest number: The function finds the maximum valued item in the array recursively.
                            3.Calculate sum: The function calculates the sum of items in the array recursively. 
                            4.Calculate standard deviation: The function calculates the mean and the standard deviation of the array recursively.
                            5.Exit: Terminates the menu function.
                            
                    Part 2: Recursive function that prints all possible orientation sets that covers the entire field with Lshaped pipes (starting from the top-left corner of the field).
                    Part 3: Recursive function that removes duplicated characters in a given string.
Part 2 =>               
![Ekran görüntüsü 2022-02-19 014226](https://user-images.githubusercontent.com/76924597/154772387-6d3e71b4-0f19-496f-a973-899d7fd091a6.png)

Printed Sequence of Part 2 =>

![image](https://user-images.githubusercontent.com/76924597/154772715-34ef5993-f084-4ebf-95d0-2e1f4f18b512.png)

                    

&emsp;&emsp;PROJECT 9

    1901042643.c => 1.Returns the number of paths Player could take back to the origin from the specified starting position,
                      subject to the condition that Player doesn’t want to take any unnecessary steps and can therefore only
                      move west or south (left or down in the diagram).
                    2.Function that accepts as input the set of all cities and a list of the cities that would be covered by each
                      hospital,along with the maximum number of hospitals that can be constructed, and returns whether or not it is
                      possible to provide coverage to all cities using the limited number of hospitals. If so, function would update
                      the result parameter to contain one such choice of hospitals
                    3.Shuffles deck by face and suit struct.
    
&emsp;&emsp;PROJECT 10
      
    1901042643.c => 2D Objects: There are three kinds of geometric objects.
                      Point: A point is defined by its two coordinates and a name.
                      Line: A line is defined by two points and a name.
                      Polygons: A circularly connected set of lines with at most 20 components.
                                It can be defined either by connecting a set of points or a set of lines.
                    
                    Actions: The following actions can be defined over the 2D objects provided in the data part of the file.
                      Distance: Print the distance between two points.
                      Distance: Print the distance between a point and a line.
                      Angle: Print the angle (in degrees) between two lines.
                      Length: Print the length of a given line. 
                      Length: Print the length (circumference) of a given polygon.
                      Area: Print the area of a given polygon.
                      
&emsp;&emsp;PROJECT 11

    1901042643.c => Part 1: The program reads a text file named ‘list.txt’. This file contains a great number of comma
                            seperated random positive integers. The program should read this file only once and store 
                            these numbers in the given order. Find stats(speed) about min,max,mean and standard deviation of
                            these numbers for both linked list or array.
                    
                    Part 2: Write a function that takes two arguments holding a large number of integers. The first argument
                            is an array allocated from the heap, and the second is a linked list. It is assumed that these
                            two arguments are holding the same sequence of integers. However, for some reason, a few of the
                            entries are entered wrong. Your function will find the difference in the entries and return them
                            in a separate array 

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

