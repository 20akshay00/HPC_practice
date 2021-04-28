using MPI, Statistics

MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)
root = 0 #root process

if(rank == root) 
    print("Lower interval: ")
    a = parse(Float64, readline())
    print("Upper interval: ")
    b = parse(Float64, readline())
    print("Number of runs: ")
    n = parse(Int64, readline())
else 
    a = 0.0
    b = 0.0
    n = 0
end

MPI.Barrier(comm)

a = MPI.bcast(a, root, comm)
b = MPI.bcast(b, root, comm)
n = MPI.bcast(n, root, comm)

f(x) = x^2 
monteCarloIntegrate(f, a, b, n) = (b-a)*mean(x->f(a + (b-a)*x), rand(n))

partial_int = monteCarloIntegrate(f, a, b, Int(n/size))
global_int = MPI.Reduce(partial_int, +, root, comm)

println("Partial integral from process $(rank) is: $(partial_int)")

if(rank == root)
    println("=================")
    println("Integral from $(a) to $(b) over $(n) sweeps is: $(global_int/size)")
end

MPI.Finalize()