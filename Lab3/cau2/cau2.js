const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

app.use(bodyParser.json());

app.post('/sensor-data', (req, res) => {
  const { light, distance } = req.body;

  let lightIntensity = 0;
  if (light < 100) {
    lightIntensity = 3;
  } else if (light < 200) {
    lightIntensity = 2;
  } else if (light < 350) {
    lightIntensity = 1;
  }

  let message = "";
  if (distance < 100) {
    message = `Có người tiếp cận. Số lượng đèn sáng cần bật: ${lightIntensity}`;
  } else {
    message = "Không có người tiếp cận. Tắt các đèn.";
    lightIntensity = 0;
  }

  const response = {
    error: false,
    message: "This is a message of API",
    data: {
      light_intensity: lightIntensity
    }
  };
  res.json(response);

  console.log(message);
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});