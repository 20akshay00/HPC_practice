### A Pluto.jl notebook ###
# v0.14.2

using Markdown
using InteractiveUtils

# ╔═╡ c8576284-9549-11eb-09a9-49c73a096836
begin
	using PlutoUI
	using Plots
	using SparseArrays
    using LinearAlgebra
end

# ╔═╡ 4dce2ef1-30dd-45db-90f4-c3e8597089a6
html"<style>
main {
    max-width:75%;
    padding: unset;
    margin-right: unset !important;
    margin-bottom: 20px;
    align-self: center !important;
}
pluto-helpbox {
    visibility: hidden;
}
</style>"

# ╔═╡ 208cbf8a-954a-11eb-31c8-014c1b072be0
function initCond(xgrid, sType, μ, σ, p)
	
    if(sType == 1) #moving gaussian
       return Complex.(1/(σ*sqrt(2*π)) * exp.(p*im*xgrid - ((xgrid .- μ) .^2 ./ (4*σ^2))))
	end
end

# ╔═╡ 1fc331e4-954a-11eb-28ba-d17a94789af9
function schrodingerEquation(dx::Float64, xi::Float64, xf::Float64, m::Int64, dt::Float64, mass::Float64, momentum::Float64, potential)
    
    xgrid = collect(xi:dx:xf) #discretized spatial grid
    n = length(xgrid)
	
	V = potential.(xgrid)
	#maxV = max.(V)
	
	#CREATING EVOLUTION MATRIX
	diag = ones(Complex, n)
	α = im*dt/(4*mass*dx^2) * diag[2:end]
	ξ = 1 .+ (im * dt/2) * (1/(mass*dx^2) .+ V)
	γ = 1 .- (im * dt/2) * (1/(mass*dx^2) .+ V)
	
    M₁ = LinearAlgebra.SymTridiagonal(ξ,-α)
    M₂ = LinearAlgebra.SymTridiagonal(γ, α)
	
    #INITIAL CONDITIONS
	ψ = zeros(Complex, (n, m))
    ψ[:, 1] = initCond(xgrid, 1, -0.0, 2, momentum)
    
	#TIME EVOLUTION LOOP
    for j in 1:(m-1)
		ψ[:, j+1] = M₁\(M₂*ψ[:, j])
    end
    
	
    #GIF CREATION
    anim = @gif for j = 1:10:m
		plot(xgrid, abs2.(ψ[:, j]), ylim = (-0.05, 0.1))
    end
    
    return anim
end

# ╔═╡ 270699fa-954a-11eb-3e5b-f1dbdaca0fad
function V(x)
	#return (x > -5 && x < 5) ? 3 : 0.0
	#return 0
	return 0.05*x^2
end

# ╔═╡ b15fff98-22f9-4689-957f-348dbd5dd02d
schrodingerEquation(0.01, -25.0, 25.0, 1000, 0.025, 1.0, 0.0, V)

# ╔═╡ Cell order:
# ╟─4dce2ef1-30dd-45db-90f4-c3e8597089a6
# ╠═c8576284-9549-11eb-09a9-49c73a096836
# ╠═208cbf8a-954a-11eb-31c8-014c1b072be0
# ╠═1fc331e4-954a-11eb-28ba-d17a94789af9
# ╠═270699fa-954a-11eb-3e5b-f1dbdaca0fad
# ╠═b15fff98-22f9-4689-957f-348dbd5dd02d
