clear
n = 10
max = 100

A = randi(max, n)


b = randi([-max, max], n, 1)
bt = transpose(b) #könnyebb bemásolni

[L, U] = lu(A)

b_alt = linsolve(L, b)
x = linsolve(U, b_alt)

