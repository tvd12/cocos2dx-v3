// Playground - noun: a place where people can play

import Cocoa

var str = "Hello, playground"
println(str);
var myName: String;
myName = "dung ta van";
var reversed = ["dung", "Anh", "duong"];
var arr = sorted(reversed, {(s1:String, s2:String) -> Bool in
    return s1 < s2;
});

for str in arr {
    print(str + " ");
}

println();

for var i = 0 ; i < arr.count ; i++ {
    print(arr[i] + " ");
}

println();

enum MyFriend {
    case duc
    case lang
    case duong
};

var mf = MyFriend.duc;
switch mf {
case .duc:
    println("hello duc");
    break;
case .lang:
    println("hello lang");
    break;
default:
    println("hello anyone");
    break;
};

enum Day {
    case D1(Int, Int, Int)
    case D2(String)
};

var day = Day.D1(30, 05, 1992);
switch day {
case .D1(let d, let m, let y):
    println("my birthday: \(d), \(m), \(y).");
    break;
case .D2(let name):
    println("my name is : \(name).");
    break;
default:
    println("invalid value");
    break;
};

class People {
    var name: String = "Dung ta van";
    var age: Int = 22;
    init(name: String) {
        self.name = name;
    }
    func toString() -> String {
        return self.name + ", " + String(self.age);
    }
    
    func setFullName(let firstName: String, let lastName: String,
        let xname: String) {
            self.name = firstName + " " + lastName + " - " + xname;
    }

};

class Flower {
    func Flower(let pName: String) {
    self.name = pName;
    };
    private var name: String = "rose";
};

var dung = People(name: "Dung");
dung.name = "dung";
dung.age = 20;
dung.setFullName("Ta Van", lastName: "Dung", xname: "tvd");
var rose = Flower();

if dung === rose {
    println("rose and dung are instance of People");
}
else {
        println("rose and dung are not instance of People");
}

println("People is: \(dung.toString())");

struct Point {
    var x = 10, y = 10;
    mutating func add(let dx: Int, let dy: Int) {
        x += dx; y += dy;
    }
    
};


class PointList {
  
    init() {
        size = 0;
        mListPoint = [Point]();
    }
    
    subscript(let index: Int) -> Int {
    
        set {
            mListPoint[index] = Point();
        }
        
        get {
            return 1 + index;
        }
        
    }
    var mListPoint: [Point];
    var size: Int;
}

var pList = PointList();
println(pList[10]);











