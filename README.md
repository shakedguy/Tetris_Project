# Tetris_Project
First project - object-oriented programming in CPP
-------------------------------------------------------
Submit date: April 12th 2021.
-------------------------------------------------------
Submit students:

Full name: Guy Shaked.
ID: 205717952.
Cell: 054-2422521.
Email: shakedguy94@gmail.com

Full name: Gur shmuelevitz.
ID: 207423625.
Cell: 053-5304046.
Email: gur_Shmu@hotmail.com

-------------------------------------------------------
The project was written as part of the first homework assignment in the object-oriented programming course of the lecturer
Mr. Amir Kirsch, at the Tel Aviv-Yafo Academic College.
The project is written in CPP on a Windows operating system,
No running attempts were made on other operating systems.
The project has a header file called Public_const_and_structs which contains all the definitions of the project
constants as well as the declarations of the used libraries and names,
also each class has a header file containing the department definition, its data members and declarations of its member functions,
and a cpp file containing the definitions of the department's functions.

-------------------------------------------------------
Bonuses on the second submission:

The algorithm for selecting the location of the computer player is-

1. Selects the lowest position that completes the maximum number of rows.

	If there is no position that completes a row -
2. Inserting to a vector blocks whose head (point 0,0 in their matrix)
   is in the lowest position, or the blocks whose tail (the end of their shape) reaches the lowest position.

3. Selects the position that brings a row to a situation that has only one empty cell left,
   and whose position is equal to the lowest or higher position by at most 2 rows.

	If there is no position that bring a row to a "One to go" situation -
4. Selects the position that does not block empty cells in the rows below it,
   And its position is equal to the lowest or highest position at most 2 rows.

	If it hasn't found any position with a better priority -
5. Select the lowest position.

