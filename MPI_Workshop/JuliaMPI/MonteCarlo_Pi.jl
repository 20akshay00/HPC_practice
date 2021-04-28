using MPI, Statistics

MPI.Init()

comm = MPI.COMM_WORLD
rank = MPI.Comm_rank(comm)
size = MPI.Comm_size(comm)
root = 0 #root process

a = (-1, -1)
widths = (2, 2)
n = Int(1e6) 

f((x, y)) = (x^2 + y^2 > 1) ? 0 : 1

monteCarloIntegrate(f, a, widths, n) = prod(widths)*mean([f(widths .* rand(length(a)) .+ a) for i in 1:n])

partial_int = monteCarloIntegrate(f, a, widths, n)
global_int = MPI.Reduce(partial_int, +, root, comm)

println("Partial integral from process $(rank) is: $(partial_int)")

if(rank == root)
    println("=================")
    println("Pi is found to be $(global_int/size)")
end

MPI.Finalize()