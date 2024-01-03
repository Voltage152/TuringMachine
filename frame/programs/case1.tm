; This program implement the multiplication operation of a decimal number
; Input: A string of the form a^i b^j, and i, j > 0

#Q = {0,A,B,C,dead,final_hault,move_a,move_b,dead1,dead2,dead3,dead4,dead5,dead6,dead7,dead8,dead9,dead10,dead11,dead12,dead_dead}

#S = {a,b}

#G = {a,b,c,_,I,l,e,g,n,p,u,t}

#q0 = 0

#B = _

#F = {final_hault}

#N = 3

;State 0, start state
0 a__ a__ *** A     ;trans to A
0 b__ b__ *** dead  ;num of a = 0

;State A, check 'a'
A a__ _a_ rr* A     ;if read a, put a to tape2
A b__ b__ *** B     ;if read b, trans to B

;State B, check 'b'
B b__ __b r*r B     ;if read b, put b to tape3
B a__ a__ *** dead  ;if read a, dead
B ___ ___ *ll C     ;if all a and b have been read,begin the print of 'c'

;State C, start to print 'c'
C _ab cab r*l C             ;print 'c' for b times
C _a_ _a_ **r move_b         ;b move to blank ,need to move b back
C __* __* *** final_hault   ;a move to blank, finish

;State move_b
move_b _*b _*b **r move_b   ;move b to the left blank
move_b _*_ _*_ **l move_a   ;b move to left b, trans to move_a

;State move_a
move_a _a* _a* *l* C        ;move a left, and continue print c

;State dead, print "Illegal_Input"
dead *__ ___ r** dead       ;clear all input on tape1

;print Illegal_Input
dead ___ I__ r** dead1
dead1 ___ l__ r** dead2
dead2 ___ l__ r** dead3
dead3 ___ e__ r** dead4
dead4 ___ g__ r** dead5
dead5 ___ a__ r** dead6
dead6 ___ l__ r** dead7
dead7 ___ ___ r** dead8
dead8 ___ I__ r** dead9
dead9 ___ n__ r** dead10
dead10 ___ p__ r** dead11
dead11 ___ u__ r** dead12
dead12 ___ t__ r** dead_dead