#include "postOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}


//--------

// TODO
vector<Mail *> PostOffice::removePostman(string name) {
	vector<Mail *> res;
    for(int i=0; i<postmen.size(); i++)
    {
        if (postmen[i].getName()==name)
        {
            vector<Mail *> mail=postmen[i].getMail();
            postmen.erase(postmen.begin()+i);
            return mail;
        }
    }
	return res;
}

// TODO
vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
	vector<Mail *> res;
    balance=0;
    for(int i=0; i<mailToSend.size(); i++)
    {
        RegularMail *mail = dynamic_cast<RegularMail *> (mailToSend[i]);
        if(mail!=NULL)
            balance+=mail->getPrice();
        else
        {
            GreenMail *gmail = dynamic_cast<GreenMail *> (mailToSend[i]);
            if(gmail!=NULL)
                balance+=gmail->getPrice();
        }
        if(mailToSend[i]->getZipCode()>=firstZipCode && mailToSend[i]->getZipCode()<=lastZipCode)
            addMailToDeliver(mailToSend[i]);
        else
            res.push_back(mailToSend[i]);
        mailToSend.erase(mailToSend.begin()+i);
        i--;
    }

	return res;
}


Postman PostOffice::addMailToPostman(Mail *m, string name) {
	for (auto person: postmen)
    {
        if(person.getName()==name)
        {
            person.addMail(m);
            return person;
        }
    }
    NoPostmanException e(name);
    throw(e);
}

