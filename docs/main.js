const observer = new IntersectionObserver(entries => {
    // Loop over the entries
    entries.forEach(entry => {
        // If the element is visible
        if (entry.isIntersecting) {
            // Add the animation class
            entry.target.classList.add('slide-up-animation');
        }
    });
});

const docObserver = new IntersectionObserver(entries => {
    // Loop over the entries
    entries.forEach(entry => {
        // If the element is visible
        if (entry.isIntersecting) {
            // Add the animation class
            setTimeout(function(){
                document.getElementById("docs").classList.add("fade-in-animation");
                document.getElementById("docs").style.opacity = 1;
            }, 900);
        }
    });
});

docObserver.observe(document.getElementById("docs"));

observer.observe(document.querySelector('.slide-up'));

var i = 0;
var txt = `truth = 'this is the worst code demo ever'
        print('Why would anyone look at this demo, ' + truth)
        print('I am not even sure if this is a joke')
        strToIter = "lol"
        
        for char : strToIter do {
            \tprint(char)
        }
        
        for i = 0 to 5 do {
            \tprint(i)
        }
        
        i = 0
        while i < lenOf(strToIter) do {
            \tprint(strToIter ? i)
            \ti += 1
        }
        
        print("somehow this all compiled without a memory error in my test interpreter")
    `;
var speed = 50;
function typeWriter() {
    if (i < txt.length) {
        if(txt.charAt(i) == '\n'){
            document.getElementById("text-editor").innerHTML += "<br>";
        } else if(txt.charAt(i) == '\t'){
            document.getElementById("text-editor").innerHTML += "&nbsp;&nbsp;&nbsp;&nbsp;";
        } else{
            document.getElementById("text-editor").innerHTML += txt.charAt(i);
        }
        i++;
        setTimeout(typeWriter, speed);
    }
}

typeWriter();