/*
    source:
    https://stackoverflow.com/questions/62161819/what-exactly-is-the-text-location-hash-in-an-url
*/
function search() {
    text = document.querySelector('#searchBox').value;
    var x = document.URL + `#:~:text=${text}`;
    window.close();
    window.open(x);
};


/* 
    I tried to blur the body while displaying the image
    but it turns out that, applying a CSS-Filter on the parent breaks the child fixed positioning.

    source:
    https://stackoverflow.com/questions/52937708/why-does-applying-a-css-filter-on-the-parent-break-the-child-positioning

    So I decided to change the opacity(#textBlock) to somehow focus on image.
*/
function show(img) {
    document.getElementById(img).style.visibility = 'visible';
    document.getElementById(img).style.maxHeight = '75%';
    document.getElementById("textBlock").style.background = 'rgba(0, 0, 0, 0)'; 
}

function hide(img) {
    document.getElementById(img).style.visibility = 'hidden';
    document.getElementById(img).style.maxHeight = '0px';
    document.getElementById("textBlock").style.background = 'rgba(0, 0, 0, 0.8)';
}

/* 
    I found these while trying to find a way to pause/cycle my carousel.
*/
$('.close').click(function () {
    $('#slides').carousel('cycle');
});

$('.lords').click(function () {
    $('#slides').carousel('pause');
});
