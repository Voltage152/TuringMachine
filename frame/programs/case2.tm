; This program determines whether c is consistent before and after
; Input: A string of the form ucu

#Q = {0,move,move2,check,final_hault,accept,accept1,accept2,accept3,accept4,reject,reject1,reject2,reject3,reject4,reject5,reject_reject}

#S = {a,b,c}

#G = {a,b,c,_,t,r,u,e,f,a,l,s}

#q0 = move

#B = _

#F = {final_hault}

#N = 2

;State move
move a_ _a rr move
move b_ _b rr move
move c_ __ rl move2
move __ __ ** reject    ;no 'c'

;State move2
move2 ** ** *l move2    ;move tape2's pointer to the begin
move2 _* _* *l move2    ;move pointer, but tape1 is empty
move2 *_ *_ *r check    ;trans check
move2 __ __ *r check    ;trans check, but tape1 is empty
move2 __ __ ** check    ;tape1 is empty

;State check
check aa __ rr check
check bb __ rr check
check __ __ ** accept

check ab __ r* reject
check ba __ r* reject   
check *_ __ r* reject   ;left not end, right end
check _* __ r* reject   ;left end, right not end
check c* __ r* reject   ;left is c, right is a or b
check *c __ r* reject   ;left is a or b, right is c

;State accept
accept __ t_ r* accept1
accept1 __ r_ r* accept2
accept2 __ u_ r* accept3
accept3 __ e_ r* final_hault

;State reject
reject ** __ rr reject
reject *_ __ r* reject
reject __ __ ** reject1
reject1 __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ r* reject_reject
