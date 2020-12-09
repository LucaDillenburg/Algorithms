package main;

import (
	"fmt"
	"errors"
)

type modularEquation struct {
	remainer int64
	mod int64
}

func gcdExtended(a int64, b int64, x *int64, y *int64) int64 { 
    if a == 0 { 
		*x = 0
		*y = 1
        return b
    } 
  
    var x1, y1 int64
    gcd := gcdExtended(b%a, a, &x1, &y1)
  
    *x = y1 - (b/a) * x1
    *y = x1
  
    return gcd
} 

func inverseMod(remainer int64, mod int64) (int64, error) {
	var x, y int64
    g := gcdExtended(remainer, mod, &x, &y)
    if g != 1 {
		return 0, errors.New("Inverse doesn't exist")
	} else {
        res := (x%mod + mod) % mod
		return res, nil
    }
}

func getModsProduct(equations []modularEquation) int64 {
	modsProduct := int64(1)
	for _, equation := range equations {
		modsProduct *= equation.mod
	}
	return modsProduct
}

func solveModularEquation(equations []modularEquation) (int64, error) {
	modsProduct := getModsProduct(equations)

	x := int64(0)
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
	var amnt int64
	fmt.Print("How many modular equations are you going to write? ")
	fmt.Scanf("%d%d", &amnt)

	fmt.Println()
	fmt.Println("Consider the equations on the form: \"X mod M = A mod M\".")
	fmt.Println("Write the As in separated lines.")
	fmt.Println("For example, if you want to refer to equations: (X mod 5 = 12 mod 5) and (X mod 7 = 6 mod 7), you should write: 12 [ENTER] 6.")
	fmt.Println("Write the numbers below in separated lines.")

	equations := make([]modularEquation, amnt)
	for i:=0; i<len(equations); i++ {
		var remainer int64
		fmt.Scanf("%d", &remainer)
		equations[i].remainer = remainer
	}

	fmt.Println()
	fmt.Println("Consider the equations on the form: \"X mod M = A mod M\".")
	fmt.Println("Write the Ms in separated lines.")
	fmt.Println("For example, if you want to refer to: \"X mod 5 = 12 mod 5\" and \"X mod 7 = 6 mod 7\", write: 5 [ENTER] 7.")
	fmt.Println("Write the numbers below in separated lines.")

	for i:=0; i<len(equations); i++ {
		var mod int64
		fmt.Scanf("%d", &mod)
		equations[i].mod = mod
	}

	fmt.Println()
	fmt.Println("Equations: ")
	for _, equation := range equations {
		fmt.Printf("X mod %d = %d mod %d", equation.mod, equation.remainer, equation.mod)
		fmt.Println()
	}

	res, err := solveModularEquation(equations)
	fmt.Println()
	if err != nil {
		fmt.Printf("Error: %s\n", err)
	} else {
		modsProduct := getModsProduct(equations)
		fmt.Println("Answer:")
		fmt.Printf("X mod %d = %d \n", modsProduct, res)
	}
}
