struct Puupu {
    var firstName: String
    var lastName: String

    func sayHello(){
        print("hello there my name is \(firstName) \(lastName).")
    }    
}

let sohaib = Puupu(firstName: "sohaib", lastName: "marchich")
let oussama = Puupu(firstName: "osama", lastName: "marchich")

sohaib.sayHello()
oussama.sayHello()