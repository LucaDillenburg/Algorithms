package main;

import (
	"fmt"
	"errors"
)

type modularEquation struct {
	remainer int
	mod int
}

func gcdExtended(a int, b int, x *int, y *int) int { 
    if a == 0 { 
		*x = 0
		*y = 1
        return b
    } 
  
    var x1, y1 int
    gcd := gcdExtended(b%a, a, &x1, &y1)
  
    *x = y1 - (b/a) * x1
    *y = x1
  
    return gcd
} 

func inverseMod(remainer int, mod int) (int, error) 
	var x, y int
    g := gcdExtended(remainer, mod, &x, &y)
    if g != 1 {
		return 0, errors.New("Inverse doesn't exist")
	} else {
        res := (x%mod + mod) % mod
		return res, nil
    }
}

func solveModularEquation(equations []modularEquation) (int, error) {
	modsProduct := 1
	for _, equation := range equations {
		modsProduct *= equation.mod
	}

	x := 0
	for _, equation := range equations {
		modProductWithoutCurMod := modsProduct / equation.mod
		remainerInverse, err := inverseMod(modProductWithoutCurMod, equation.mod)
		if err != nil {
			return 0, err
		}

		x += equation.remainer * modProductWithoutCurMod * remainerInverse
	}

	return x % modsProduct, nil
}

func main() {
	var amnt int
	fmt.Print("How many modular equations are you going to write?")
	fmt.Scanf("%d%d", &amnt)

	fmt.Println("Consider the equations on the form X mod M = A.")
	fmt.Println("Write the As in separated lines.")
	fmt.Println("For example, if you want to refer to: X mod 5 = 12 (mod 5) and X mod 7 = 6, write: 12 [ENTER] 6.")

	equations := make([]modularEquation, amnt)
	for i:=0; i<len(equations); i++ {
		var remainer int
		fmt.Scanf("%d", &remainer)
		equations[i].remainer = remainer
	}

	fmt.Println("Write the Ms in separated lines.")
	fmt.Println("For example, if you want to refer to: X mod 5 = 12 and X mod 7 = 6, write: 5 [ENTER] 7.")

	for i:=0; i<len(equations); i++ {
		var mod int
		fmt.Scanf("%d", &mod)
		equations[i].mod = mod
	}

	fmt.Println()
	fmt.Println("Equations: ")
	for _, equation := range equations {
		fmt.Printf("X mod %d = %d", equation.mod, equation.remainer)
		fmt.Println()
	}

	res, err := solveModularEquation(equations)
	fmt.Println()
	if err != nil {
		fmt.Printf("Error: %s", err)
	} else {
		fmt.Printf("X = %d \n", res)
	}
}
