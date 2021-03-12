fetch('http://localhost:7071/api/GetDataFromCosmos')
.then(res => res.json())
.then(data => {
    for(let d of data) {
        document.getElementById('app').innerHTML += `
        <div>
            <h5>${d.deviceId}</h5>
            <p>Temperature: ${d.temperature}, Humidity: ${d.humidity}, TimeStamp: ${d._ts}</p>
            <p> class="text-muted">${d.name} (${d.school})</p>
        </div>`
    }
})