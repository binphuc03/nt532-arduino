const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const PORT = 3000;

app.use(bodyParser.json());

// API endpoint nhận dữ liệu từ Wemos D1
app.post('/data', (req, res) => {
    const data = req.body;
    const { light, distance } = data;
    console.log(`Received data - Light: ${light}, Distance: ${distance}`);
    // Xử lý dữ liệu ở đây
    // Trả về phản hồi
    res.json({ error: false, message: "Data received successfully", data: null });
});

// API endpoint xác định số lượng đèn sáng cần thiết
app.get('/lights', (req, res) => {
    const distance = req.query.distance;
    console.log(`Received request for lights calculation - Distance: ${distance}`);
    // Xử lý và tính toán số lượng đèn sáng dựa trên distance
    const lights = calculateLights(distance);
    // Trả về kết quả
    res.json({ error: false, message: "Number of lights determined", data: { lights } });
});

// Hàm tính toán số lượng đèn sáng
function calculateLights(distance) {
    // Logic tính toán số lượng đèn sáng
    // Đây chỉ là một ví dụ đơn giản
    return Math.round(distance / 100); // Giả sử 1 đèn sáng cho mỗi 100 đơn vị khoảng cách
}

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
