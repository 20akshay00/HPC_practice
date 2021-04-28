# copied from dhruva


using MPI

MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)

print("Rank $(rank), Size $(size)\n")

xi, xf, m = 0, pi, 1000
dx = (xf-xi)/m

function simpson(f, xi, m, dx)
    intg = f(xi) + f(xi+m*dx)
    intg += 4 * sum(1:2:(m-1)) do i; f(xi + i*dx); end # the odd guys
    intg += 2 * sum(2:2:(m-1)) do i; f(xi + i*dx); end # the even guys
    intg * dx/3
end

function trap(f, xi, m, dx)
    intg = (f(xi) + f(xi+m*dx))/2
    intg += sum(1:(m-1)) do i; f(xi + i*dx); end
    intg*dx
end

localint = simpson(cos, xi + rank*(m÷size)*dx, (m÷size), dx)
MPI.Send(localint, 0, 0, comm)

if rank == 0
    localints = map(0:size-1) do sender
        MPI.Recv(Float64, sender, 0, comm)[1]
    end
    println("\nResults from processes:\n ", localints)
    globalint = sum(localints)
    println(globalint)
    if m%size != 0
        laggers = simpson(cos, xi+size*m÷size*dx, m%size, dx)
        println("Laggers, ", laggers)
        globalint += laggers
    end
    println(globalint)
end