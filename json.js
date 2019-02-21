const datastorageList = document.querySelector('#cafe-list');
function renderCafe(doc){
    let li = document.createElement('li');
    let time = document.createElement('span');

    li.setAttribute('data-id', doc.id)
    time.textContent = doc.data().time;
    
    li.appendChild(time);
    datastorageList.appendChild(li);
}

db.collection('datastorage').get().then((snapshot) => {
    snapshot.docs.forEach(doc => {
        renderCafe(doc);
    })
})
  