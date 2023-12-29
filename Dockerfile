FROM gcc:latest

EXPOSE 80:80/tcp

COPY . .

CMD ["make", "run"]