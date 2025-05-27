FROM debian:bookworm-slim
COPY ../bin/cliente /app/cliente
WORKDIR /app
CMD ["./cliente"]
