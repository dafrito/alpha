local t = 0
function Tick(square, elapsed)
	t = t + elapsed
	square.x = 50 * math.cos(t);
end
