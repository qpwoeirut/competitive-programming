from stub import use_machine

def count_mushrooms(n: int) -> int:
	m = []
	for i in range(n):
		m.append(i)
	c1: int = use_machine(m)
	m = [0, 1]
	c2: int = use_machine(m)
	return c1+c2
