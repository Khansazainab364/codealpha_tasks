let images = [
"https://picsum.photos/id/1015/800/600",
"https://picsum.photos/id/1011/800/600",
"https://picsum.photos/id/1018/800/600",
"https://picsum.photos/id/1025/800/600",
"https://picsum.photos/id/1035/800/600",
"https://picsum.photos/id/1040/800/600"
];

let index = 0;
let zoomLevel = 1;

/* SHOW GALLERY */
function showGallery() {
  document.getElementById("home").style.display = "none";
  document.getElementById("gallery-page").style.display = "block";
}

/* BACK */
function goHome() {
  document.getElementById("gallery-page").style.display = "none";
  document.getElementById("home").style.display = "flex";
}

/* LIGHTBOX */
function openLightbox(i) {
  index = i;
  document.getElementById("lightbox").style.display = "flex";
  document.getElementById("lightbox-img").src = images[index];
}

function closeLightbox() {
  document.getElementById("lightbox").style.display = "none";
  zoomLevel = 1;
  document.getElementById("lightbox-img").style.transform = "scale(1)";
}

/* NEXT PREV */
function nextImage() {
  index = (index + 1) % images.length;
  document.getElementById("lightbox-img").src = images[index];
}

function prevImage() {
  index = (index - 1 + images.length) % images.length;
  document.getElementById("lightbox-img").src = images[index];
}

/* ZOOM */
function zoomIn() {
  zoomLevel += 0.2;
  document.getElementById("lightbox-img").style.transform =
    "scale(" + zoomLevel + ")";
}

function zoomOut() {
  if (zoomLevel > 1) {
    zoomLevel -= 0.2;
    document.getElementById("lightbox-img").style.transform =
      "scale(" + zoomLevel + ")";
  }
}

/* CLICK ZOOM */
document.addEventListener("DOMContentLoaded", () => {
  document.getElementById("lightbox-img").addEventListener("click", function () {
    if (zoomLevel === 1) {
      zoomLevel = 2;
    } else {
      zoomLevel = 1;
    }
    this.style.transform = "scale(" + zoomLevel + ")";
  });
});

/* FILTER */
function filterImages(category) {
  let items = document.getElementsByClassName("img-box");

  for (let i = 0; i < items.length; i++) {
    if (category === "all" || items[i].classList.contains(category)) {
      items[i].style.display = "block";
    } else {
      items[i].style.display = "none";
    }
  }
}