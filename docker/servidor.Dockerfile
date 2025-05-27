FROM debian:bookworm-slim
COPY ../bin/servidor /app/servidor
WORKDIR /app
EXPOSE 3000
CMD ["./servidor"]
