const btn = document.getElementById('menu-btn');
const menu = document.getElementById('mobile-menu');

btn.addEventListener('click', () => {
    menu.classList.toggle('hidden')
    const icon = btn.querySelector('i');
    icon.classList.toggle('fa-bars-staggered');
    icon.classList.toggle('fa-xmark');
});

document.querySelectorAll('#mobile-menu a').forEach(link => {
    link.addEventListener('click', () => {
        menu.classList.add('hidden');
    });
});

const reviews = [
    { name: "Vivianne West", rating: 2, msg: "The level of detail at Aurum is unmatched. A masterpiece." },
    { name: "Marcus Reed", rating: 5, msg: "Julian has an incredible eye for structure. Best cut in NYC." },
    { name: "Elena S.", rating: 5, msg: "The golden hour balayage changed my entire look. Highly recommend!" },
    { name: "James Sterling", rating: 5, msg: "Exceptional service from the moment you walk in the door." },
    { name: "Sophia L.", rating: 2, msg: "Finally found a stylist who understands texture and movement." },
    { name: "Catherine D.", rating: 4, msg: "Luxury at its finest. The ritual treatment is a must-try." },
    { name: "Robert Fox", rating: 5, msg: "Professional, clean, and masterfully skilled team." },
    { name: "Isabella Rossi", rating: 5, msg: "Sofia saved my hair. Her trichology knowledge is profound." },
    { name: "Liam Chen", rating: 5, msg: "The only place I trust for my signature style." },
    { name: "Ava Montgomery", rating: 5, msg: "Absolute gold standard. My hair has never been healthier." },
    { name: "David Miller", rating: 5, msg: "Precision cutting like I've never experienced before." },
    { name: "Emma Wilson", rating: 5, msg: "The atmosphere is so tranquil and the results are stunning." },
    { name: "Noah Williams", rating: 4, msg: "Top tier experts. Great attention to detail." },
    { name: "Olivia Brown", rating: 5, msg: "I travel 2 hours just to see Julian. Worth every mile." },
    { name: "Lucas Garcia", rating: 5, msg: "Best experience ever. The consultation was very thorough." },
    { name: "Mia Martinez", rating: 5, msg: "Elena is a magician with color. Simply perfect." },
    { name: "Ethan Hunt", rating: 5, msg: "Classy, elegant, and efficient. 10/10." },
    { name: "Charlotte Lee", rating: 5, msg: "My hair felt like silk after the velvet treatment." },
    { name: "Amelia Taylor", rating: 5, msg: "Truly a bespoke experience. They listen and deliver." },
    { name: "Benjamin Moore", rating: 5, msg: "The grooming here is top notch. Very professional." }
];

const reviewContainer = document.getElementById('review-content');

function createReviewHTML(review) {
    let stars = '';
    for (let i = 0; i < 5; i++) {
        stars += `<i class="fa-solid fa-star ${i < review.rating ? 'text-[#D4AF37]' : 'text-stone-700'} text-[8px] mr-1"></i>`;
    }
    return `
                <div class="review-card">
                    <div class="flex justify-between items-center mb-4">
                        <span class="brand text-xs tracking-[0.3em] gold-text">${review.name}</span>
                        <div>${stars}</div>
                    </div>
                    <p class="text-stone-400 italic text-sm leading-relaxed">"${review.msg}"</p>
                </div>
            `;
}

const allReviews = [...reviews, ...reviews];
reviewContainer.innerHTML = allReviews.map(r => createReviewHTML(r)).join('');


function showToast(message) {
    const container = document.getElementById('toast-container');
    const toast = document.createElement('div');
    toast.className = 'gold-toast';
    toast.innerHTML = `<i class="fa-solid fa-bell-concierge mr-2 text-[#D4AF37]"></i> ${message}`;
    container.appendChild(toast);

    setTimeout(() => {
        toast.style.opacity = '0';
        toast.style.transform = 'translateX(20px)';
        toast.style.transition = 'all 0.5s ease';
        setTimeout(() => toast.remove(), 500);
    }, 4000);
}

document.getElementById('booking-form').addEventListener('submit', function (e) {
    e.preventDefault();

    const name = document.getElementById('form-name').value;
    const phone = document.getElementById('form-phone').value;
    const service = document.getElementById('form-service').value;
    const date = document.getElementById('form-date').value;

    console.log("name: ", name);
    console.log("phone: ", phone);
    console.log("service: ", service);
    console.log("date: ", date);

    // VALIDATION
    if (!name || !phone || service === "Not Specified" || !date) {
        showToast("Please complete all rituals for booking");
        return;
    }

    const appointmentData = { name, phone, service, date };
    const adminPhone = "8307782378"; // REPLACE WITH YOUR NUMBER

    const message = `*OptimizeLabs.io BOOKING REQUEST*%0A` +
        `*Client:* ${appointmentData.name}%0A` +
        `*Ritual:* ${appointmentData.service}%0A` +
        `*Date:* ${appointmentData.date}%0A` +
        `*Phone:* ${appointmentData.phone}`;

    showToast("Redirecting to Concierge...");
    setTimeout(() => {
        window.open(`https://wa.me/${adminPhone}?text=${message}`, '_blank');
    }, 1000);
});